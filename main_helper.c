/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:15:23 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 17:18:37 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_tokens(char *line)
{
	if (g_exit_status == 2)
		return (1);
	if (ft_strchr(line, '\'') || ft_strchr(line, '"'))
	{
		printf("minishell: : command not found\n");
		g_exit_status = 127;
		return (1);
	}
	return (0);
}

void	execute_commands(t_cmd *cmds, t_node **env)
{
	expand_cmds(cmds, *env, g_exit_status);
	if (pipe_number(cmds) == 1 && cmds->redirect == NULL)
		g_exit_status = exec_cmd(cmds, env);
	else
		g_exit_status = exec_pipes(cmds, env);
	if (g_exit_status == -1)
		exit(1);
}
