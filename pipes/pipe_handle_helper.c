/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:25:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 18:31:26 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	child_process(t_pipe_info info)
{
	int	exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (info.input_fd != 0)
	{
		dup2(info.input_fd, STDIN_FILENO);
		close(info.input_fd);
	}
	if (info.has_pipe)
	{
		dup2(info.pipe_fd[1], STDOUT_FILENO);
		close(info.pipe_fd[0]);
		close(info.pipe_fd[1]);
	}
	if (handle_redirects(info.cmds, *info.env, g_exit_status) == -1)
		exit(EXIT_FAILURE);
	exit_status = exec_cmd(info.cmds, info.env);
	exit(exit_status);
}

void	parent_process_no_wait(int *input_fd, int has_pipe, int *pipe_fd)
{
	if (*input_fd != 0)
		close(*input_fd);
	if (has_pipe)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}

void	parent_process(pid_t pid, int *input_fd, int has_pipe, int *pipe_fd)
{
	int	status;

	handle_pipe_cleanup(input_fd, has_pipe, pipe_fd);
	waitpid(pid, &status, 0);
	handle_exit_status(status, 1);
}
