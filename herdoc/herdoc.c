/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:20:40 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 01:32:40 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_heredoc_input(const char *delimiter, size_t delimiter_len,
	int is_terminal, int saved_exit_status)
{
	char	*line;
	char	*content;

	content = init_heredoc_content();
	while (1)
	{
		line = read_heredoc_line(is_terminal);
		if (check_heredoc_termination(line, delimiter, delimiter_len,
				is_terminal))
			break ;
		content = append_line_to_content(content, line);
		if (is_terminal)
			free(line);
	}
	g_exit_status = saved_exit_status;
	return (content);
}

int	handle_heredoc(const char *delimiter, t_node *env, int status)
{
	char	*content;
	char	*expanded_content;
	int		pipefd[2];

	if (!delimiter)
	{
		write(STDERR_FILENO,
			"minishell: syntax error: null heredoc delimiter\n", 49);
		return (-1);
	}
	if (setup_heredoc_pipe_and_signals(pipefd) == -1)
		return (-1);
	content = process_heredoc_input(delimiter, ft_strlen(delimiter),
			isatty(STDIN_FILENO), g_exit_status);
	cleanup_heredoc(content, pipefd);
	if (!content)
		return (-1);
	if (env)
		expanded_content = expand_var_heredoc(content, env, status);
	else
		expanded_content = content;
	write_heredoc_content(expanded_content, pipefd[1]);
	return (pipefd[0]);
}
