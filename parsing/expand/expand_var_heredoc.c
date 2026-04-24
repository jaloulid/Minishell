/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:45:00 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 00:45:00 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar_heredoc(char *str, int *i, t_node *env,
		int last_exit)
{
	char	*tmp;

	(*i)++;
	tmp = expand_dollar(str, i, env, last_exit);
	return (tmp);
}

static void	process_quote_heredoc(char *str, int *i, int *in_quotes,
		char *quote_char)
{
	if (!(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = str[*i];
	}
	else
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
	(*i)++;
}

char	*expand_var_heredoc(char *str, t_node *env, int last_exit)
{
	char	*res;
	int		i;
	int		in_quotes;
	char	quote_char;

	res = ft_strdup("");
	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && (!in_quotes
				|| str[i] == quote_char))
		{
			res = append_char(res, str[i]);
			process_quote_heredoc(str, &i, &in_quotes, &quote_char);
		}
		else if (str[i] == '$')
			res = append_str(res, handle_dollar_heredoc(str, &i, env,
						last_exit));
		else
			res = append_char(res, str[i++]);
	}
	return (res);
}
