/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:00:00 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/07 01:18:55 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("heredoc pipe");
		return (-1);
	}
	return (0);
}

int	write_heredoc_content(char *content, int write_fd)
{
	if (content && *content)
	{
		write(write_fd, content, ft_strlen(content));
	}
	close(write_fd);
	return (0);
}
