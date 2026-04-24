/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:01:21 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 01:23:48 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter_match(const char *line, const char *delimiter,
		size_t delimiter_len)
{
	if (!line || !delimiter || delimiter_len == 0)
		return (0);
	if (ft_strlen(line) != delimiter_len)
		return (0);
	if (ft_strncmp(line, delimiter, delimiter_len) == 0)
		return (1);
	return (0);
}

char	*append_line_to_content(char *content, char *line)
{
	char	*new_content;

	new_content = ft_strjoin(content, line);
	content = new_content;
	new_content = ft_strjoin(content, "\n");
	content = new_content;
	return (content);
}

char	*init_heredoc_content(void)
{
	char	*content;

	content = alloc(1, ALLOC);
	content[0] = '\0';
	return (content);
}

int	process_heredoc_line(char *line, const char *delimiter,
		size_t delimiter_len, int is_terminal)
{
	if (is_delimiter_match(line, delimiter, delimiter_len))
	{
		if (is_terminal)
			free(line);
		return (1);
	}
	return (0);
}
