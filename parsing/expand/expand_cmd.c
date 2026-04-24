/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:17:31 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/08 15:39:14 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_args(t_cmd *cmd, t_node *env, int status)
{
	int		i;
	char	*tmp;
	char	*cleaned;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		tmp = expand_var(cmd->args[i], env, status);
		cleaned = remove_empty_quotes(tmp);
		cmd->args[i++] = cleaned;
	}
}

static void	expand_redirections(t_cmd *cmd, t_node *env, int status)
{
	t_redir	*r;
	char	*tmp1;

	r = cmd->redirect;
	while (r)
	{
		tmp1 = expand_var(r->file, env, status);
		r->file = tmp1;
		r = r->next;
	}
}

void	expand_cmds(t_cmd *cmds, t_node *env, int status)
{
	if (!cmds)
		return ;
	while (cmds)
	{
		expand_args(cmds, env, status);
		expand_redirections(cmds, env, status);
		cmds = cmds->next;
	}
}
