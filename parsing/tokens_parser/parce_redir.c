/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:40:07 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 01:29:00 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redir_type(t_token_type token_type)
{
	if (token_type == REDIR_IN)
		return (R_IN);
	else if (token_type == REDIR_OUT)
		return (R_OUT);
	else if (token_type == REDIR_APPEND)
		return (R_APPEND);
	else if (token_type == HEREDOC)
		return (R_HEREDOC);
	return (-1);
}

t_redir	*build_redirection(t_token *token)
{
	t_redir	*redir;

	if (!token || !token->next || !token->next->value)
		return (NULL);
	redir = alloc(sizeof(t_redir), ALLOC);
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(token->next->value);
	if (!redir->file)
		return (NULL);
	redir->type = get_redir_type(token->type);
	redir->quoted_delimiter = 0;
	if (token->type == HEREDOC && token->next->quoted)
		redir->quoted_delimiter = 1;
	redir->next = NULL;
	return (redir);
}

int	parse_redirect_token(t_token **tokens, t_cmd *cmd)
{
	t_redir	*redir;

	if (!tokens || !*tokens)
		return (0);
	redir = build_redirection(*tokens);
	if (!redir)
		return (0);
	redir_add_back(&cmd->redirect, redir);
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
	return (1);
}
