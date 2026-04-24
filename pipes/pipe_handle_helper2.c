/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:45:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 18:31:26 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe_cleanup(int *input_fd, int has_pipe, int *pipe_fd)
{
	if (*input_fd != 0)
		close(*input_fd);
	if (has_pipe)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}

void	handle_exit_status(int status, int is_last_cmd)
{
	if (is_last_cmd)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}
