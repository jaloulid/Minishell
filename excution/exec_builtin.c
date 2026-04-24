/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:00:00 by nesta             #+#    #+#             */
/*   Updated: 2025/08/09 20:38:20 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_builtin_command(char **cmd, t_node **env)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd[1], env));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, env));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(cmd));
	return (-1);
}

static int	execute_env_commands(char **cmd, t_node **env)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(*env));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, env));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(env, cmd[1]));
	return (-1);
}

int	exec_builtin(char **cmd, t_node **env)
{
	int	result;

	result = execute_builtin_command(cmd, env);
	if (result != -1)
		return (result);
	result = execute_env_commands(cmd, env);
	if (result != -1)
		return (result);
	ft_putstr_fd("Unknown builtin command:", 2);
	ft_putendl_fd(cmd[0], 2);
	g_exit_status = 127;
	return (g_exit_status);
}
