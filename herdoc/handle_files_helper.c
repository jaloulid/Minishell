/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:30:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 03:11:12 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(const char *filename, int flags)
{
	int	fd;

	if (!filename)
		return (ft_putendl_fd("Error: filename is NULL", 2), -1);
	fd = open(filename, flags, 0644);
	if (fd < 0)
		return (perror("Error opening file"), -1);
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) < 0)
		return (perror("Error closing file"), -1);
	return (0);
}

int	redirect_file(int fd, int mode)
{
	if (mode == READ_MODE)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			return (perror("Error redirecting stdin"), -1);
	}
	else if (mode == WRITE_TRUNC_MODE || mode == WRITE_APPEND_MODE)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (perror("Error redirecting stdout"), -1);
	}
	return (0);
}
