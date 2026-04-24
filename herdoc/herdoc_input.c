/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:30:00 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/07 01:13:26 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resize_line_buffer(char *line, int len, int *capacity)
{
	char	*temp;

	*capacity *= 2;
	temp = alloc(*capacity, ALLOC);
	if (!temp)
		return (NULL);
	ft_memcpy(temp, line, len);
	return (temp);
}

static int	read_char_and_resize(char **line, int *len, int *capacity)
{
	char	c;
	char	*temp;
	int		bytes_read;

	bytes_read = read(STDIN_FILENO, &c, 1);
	if (bytes_read <= 0 || c == '\n')
		return (c);
	if (*len >= *capacity - 1)
	{
		temp = resize_line_buffer(*line, *len, capacity);
		if (!temp)
			return (-1);
		*line = temp;
	}
	(*line)[(*len)++] = c;
	return (c);
}

char	*read_line_from_stdin(void)
{
	char	*line;
	int		len;
	int		capacity;
	int		c;

	len = 0;
	capacity = 128;
	line = alloc(capacity, ALLOC);
	if (!line)
		return (NULL);
	while (1)
	{
		c = read_char_and_resize(&line, &len, &capacity);
		if (c <= 0 || c == '\n')
			break ;
	}
	if (c <= 0 && len == 0)
		return (NULL);
	line[len] = '\0';
	return (line);
}
