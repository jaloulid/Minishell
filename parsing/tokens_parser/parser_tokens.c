/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:40:14 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 00:37:01 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_pipe_syntax_error(t_token *tokens)
{
	if (!tokens->next)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `|'\n");
	g_exit_status = 2;
	return (0);
}

static int	handle_pipe_token(t_token *tokens, t_cmd **current)
{
	if (!tokens->next || tokens->next->type == PIPE)
		return (handle_pipe_syntax_error(tokens));
	parse_handle_pipe(current);
	return (1);
}

int	parse_one_token(t_token *tokens, t_cmd **current, t_cmd **cmds)
{
	if (tokens->type == WORD)
	{
		parse_init_cmd(current, cmds);
		parse_word_token(&tokens, *current);
		return (1);
	}
	else if (is_redirect(tokens))
	{
		parse_init_cmd(current, cmds);
		if (!parse_redirect_token(&tokens, *current))
			return (0);
		return (22);
	}
	else if (tokens->type == PIPE)
		return (handle_pipe_token(tokens, current));
	return (1);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	int		result;

	cmds = NULL;
	current = NULL;
	if (check_pipe_syntax(tokens))
		return (NULL);
	while (tokens)
	{
		result = parse_one_token(tokens, &current, &cmds);
		if (!result)
			return (NULL);
		if (result == 22)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (cmds);
}
