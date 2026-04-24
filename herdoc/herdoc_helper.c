/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:30:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/11 01:21:15 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc_line(int is_terminal)
{
	char	*line;

	if (is_terminal)
	{
		rl_done = 0;
		line = readline("> ");
	}
	else
		line = read_line_from_stdin();
	return (line);
}

int	check_heredoc_termination(char *line, const char *delimiter,
	size_t delimiter_len, int is_terminal)
{
	if (g_exit_status == 130)
	{
		if (line && is_terminal)
			free(line);
		return (1);
	}
	if (!line)
		return (1);
	if (process_heredoc_line(line, delimiter, delimiter_len, is_terminal))
		return (1);
	return (0);
}

int	setup_heredoc_pipe_and_signals(int *pipefd)
{
	if (create_heredoc_pipe(pipefd) == -1)
		return (-1);
	signal(SIGINT, heredoc_sigint_handler);
	return (0);
}

void	cleanup_heredoc(char *content, int *pipefd)
{
	signal(SIGINT, sigint_handler);
	if (!content)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
