/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:28:01 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 17:56:17 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_pipe_cmd(t_cmd *cmd, int *input_fd, t_node **env,
	pid_t *pid_out)
{
	int			pipe_fd[2];
	int			has_pipe;
	pid_t		pid;
	t_pipe_info	info;

	has_pipe = 0;
	if (cmd->next != NULL)
	{
		if (setup_pipe(pipe_fd) == -1)
			return (-1);
		has_pipe = 1;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	*pid_out = pid;
	info = (t_pipe_info){cmd, *input_fd, has_pipe, pipe_fd, env};
	if (pid == 0)
		child_process(info);
	else
		parent_process_no_wait(input_fd, has_pipe, pipe_fd);
	return (0);
}

static int	process_all_commands(t_cmd *cmds, t_node **env, pid_t *pids)
{
	int	input_fd;
	int	result;
	int	cmd_count;

	input_fd = 0;
	cmd_count = 0;
	while (cmds)
	{
		result = handle_pipe_cmd(cmds, &input_fd, env, &pids[cmd_count]);
		if (result == -1)
			return (-1);
		cmd_count++;
		cmds = cmds->next;
	}
	return (cmd_count);
}

static void	wait_for_commands(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	exec_pipes(t_cmd *cmds, t_node **env)
{
	pid_t	pids[256];
	int		cmd_count;

	cmd_count = process_all_commands(cmds, env, pids);
	if (cmd_count == -1)
		return (-1);
	wait_for_commands(pids, cmd_count);
	return (g_exit_status);
}
