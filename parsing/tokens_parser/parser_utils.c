/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:06:36 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/07 00:48:13 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = alloc(sizeof(t_cmd), ALLOC);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirect = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redir	*new_redir(char *file, t_redir_type type)
{
	t_redir	*redir;

	redir = alloc(sizeof(t_redir), ALLOC);
	if (!redir || !file)
		return (NULL);
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (NULL);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_redirect(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC);
}
