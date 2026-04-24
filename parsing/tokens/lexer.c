/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:55:06 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 01:18:04 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_operator(char *line, int *i, t_token **list)
{
	if (check_invalid_syntax(line, *i))
	{
		g_exit_status = 2;
		return (0);
	}
	handle_operator(line, i, list);
	return (1);
}

static int	process_word(char *line, int *i, t_token **list)
{
	if (handle_word(line, i, list) == -1)
	{
		print_error();
		return (0);
	}
	return (1);
}

t_token	*lexer(char *line)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (line[i])
	{
		if (check_invalid_syntax(line, i))
		{
			g_exit_status = 2;
			return (NULL);
		}
		skip_space(line, &i);
		if (!line[i])
			break ;
		if (is_operator(line[i]))
		{
			if (!process_operator(line, &i, &list))
				return (NULL);
		}
		else if (!process_word(line, &i, &list))
			return (NULL);
	}
	return (list);
}
