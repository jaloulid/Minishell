/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:15:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/11 00:21:30 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirects(t_cmd *arg, t_node *env, int status)
{
	if (arg && arg->redirect && arg->redirect->file)
	{
		if (handle_files(arg->redirect, env, status) == -1)
			return (-1);
	}
	return (0);
}

int	handle_child_process(t_cmd *cmd, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirects(cmd, NULL, 0) == -1)
		exit(1);
	if (execve(cmd->args[0], cmd->args, env) < 0)
	{
		g_exit_status = 127;
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int	handle_signal_termination(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
	else
	{
		g_exit_status = 128 + sig;
	}
	return (g_exit_status);
}

int	handle_parent_process(pid_t pid)
{
	int	status;
	int	sig;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (handle_signal_termination(sig));
	}
	return (0);
}
