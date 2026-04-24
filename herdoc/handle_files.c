/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:45:52 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/08 19:46:50 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirect(t_redir *redirect)
{
	int	fd;

	fd = open_file(redirect->file, O_RDONLY);
	if (fd == -1)
		return (-1);
	redirect_file(fd, READ_MODE);
	return (0);
}

static int	handle_output_redirect(t_redir *redirect)
{
	int	fd;

	fd = open_file(redirect->file, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (-1);
	redirect_file(fd, WRITE_TRUNC_MODE);
	return (0);
}

static int	handle_append_redirect(t_redir *redirect)
{
	int	fd;

	fd = open_file(redirect->file, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		return (-1);
	redirect_file(fd, WRITE_APPEND_MODE);
	return (0);
}

static int	process_single_redirect(t_redir *redirect)
{
	if (redirect->type == R_IN)
		return (handle_input_redirect(redirect));
	else if (redirect->type == R_OUT)
		return (handle_output_redirect(redirect));
	else if (redirect->type == R_APPEND)
		return (handle_append_redirect(redirect));
	return (0);
}

int	handle_files(t_redir *file, t_node *env, int status)
{
	t_redir	*redirect;

	if (handle_multiple_heredocs(file, env, status) == -1)
		return (-1);
	redirect = file;
	while (redirect)
	{
		if (redirect->type != R_HEREDOC)
		{
			if (process_single_redirect(redirect) == -1)
				return (-1);
		}
		redirect = redirect->next;
	}
	return (0);
}
