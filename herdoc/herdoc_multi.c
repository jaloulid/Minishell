/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:35:00 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/10 17:35:46 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*find_last_heredoc(t_redir *file)
{
	t_redir	*redirect;
	t_redir	*last_heredoc;

	last_heredoc = NULL;
	redirect = file;
	while (redirect)
	{
		if (redirect->type == R_HEREDOC)
			last_heredoc = redirect;
		redirect = redirect->next;
	}
	return (last_heredoc);
}

int	process_single_heredoc(t_redir *redirect, t_redir *last_heredoc
			, t_node *env, int status)
{
	int	fd;

	if (redirect->quoted_delimiter)
		fd = handle_heredoc(redirect->file, NULL, status);
	else
		fd = handle_heredoc(redirect->file, env, status);
	if (fd == -1)
		return (-1);
	if (redirect == last_heredoc)
		redirect_file(fd, READ_MODE);
	else
		close(fd);
	return (0);
}

int	handle_multiple_heredocs(t_redir *file, t_node *env, int status)
{
	t_redir	*redirect;
	t_redir	*last_heredoc;

	last_heredoc = find_last_heredoc(file);
	if (!last_heredoc)
		return (0);
	redirect = file;
	while (redirect)
	{
		if (redirect->type == R_HEREDOC)
		{
			if (process_single_heredoc(redirect, last_heredoc
					, env, status) == -1)
				return (-1);
		}
		redirect = redirect->next;
	}
	return (0);
}
