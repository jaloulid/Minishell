/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:45:00 by nesta             #+#    #+#             */
/*   Updated: 2025/08/10 17:22:56 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	run_builtin_forked(t_cmd *arg, char **args, t_node **env)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirects(arg, *env, g_exit_status) == -1)
			exit(1);
		exit(exec_builtin(args, env));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	return (g_exit_status);
}

static int	should_run_without_fork(char *cmd)
{
	return (ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "exit") == 0);
}

int	run_builtin(t_cmd *arg, t_node **env, char **args)
{
	if (should_run_without_fork(args[0]))
	{
		if (handle_redirects(arg, *env, g_exit_status) == -1)
			return (-1);
		return (exec_builtin(args, env));
	}
	return (run_builtin_forked(arg, args, env));
}

int	validate_external_command(char **args, t_node **env)
{
	char		*path;
	struct stat	file_stat;

	if (!args || !args[0])
	{
		ft_putendl_fd("No command provided", 2);
		g_exit_status = 127;
		return (-1);
	}
	if (args[0][0] != '/' && ft_strncmp(args[0], "./", 2) != 0
		&& ft_strncmp(args[0], "../", 3) != 0)
	{
		path = check_path(args[0], env);
		if (path)
			args[0] = path;
		else
			return (check_command_existence(args[0]));
	}
	else if (access(args[0], F_OK) == -1)
		return (check_file_existence(args[0]));
	else if (stat(args[0], &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
		return (check_is_directory(args[0]));
	else if (access(args[0], X_OK) == -1)
		return (check_file_permission(args[0]));
	return (0);
}
