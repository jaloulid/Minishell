/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 01:00:00 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 00:55:57 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_quote(char *str, t_heredoc_state *state)
{
	state->res = append_char(state->res, str[state->i]);
	if (!state->in_quotes)
	{
		state->in_quotes = 1;
		state->quote_char = str[state->i];
	}
	else
	{
		state->in_quotes = 0;
		state->quote_char = 0;
	}
	state->i++;
}

static void	handle_heredoc_dollar(char *str, t_heredoc_state *state)
{
	char	*tmp;

	tmp = expand_dollar(str, &state->i, state->env, state->last_exit);
	state->res = append_str(state->res, tmp);
}

static char	*process_heredoc_char(char *str, t_heredoc_state *state)
{
	if ((str[state->i] == '"' || str[state->i] == '\'') && (!state->in_quotes
			|| str[state->i] == state->quote_char))
		handle_heredoc_quote(str, state);
	else if (str[state->i] == '$')
		handle_heredoc_dollar(str, state);
	else
		state->res = append_char(state->res, str[state->i++]);
	return (state->res);
}

char	*expand_var_heredoc(char *str, t_node *env, int last_exit)
{
	t_heredoc_state	state;

	state.res = ft_strdup("");
	state.i = 0;
	state.in_quotes = 0;
	state.quote_char = 0;
	state.env = env;
	state.last_exit = last_exit;
	while (str[state.i])
		process_heredoc_char(str, &state);
	return (state.res);
}
