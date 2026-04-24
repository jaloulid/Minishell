/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:30:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/02 15:37:00 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path_search(t_path_search *ps, char *path, char *cmd)
{
	ps->path_len = ft_strlen(path);
	ps->cmd_len = ft_strlen(cmd);
	ps->full_path = gc_malloc(ps->path_len + 1 + ps->cmd_len + 1);
	ps->j = 0;
	ps->k = 0;
}

void	build_full_path(t_path_search *ps, char *path, char *cmd)
{
	while (ps->j < ps->path_len)
	{
		ps->full_path[ps->j] = path[ps->j];
		ps->j++;
	}
	ps->full_path[ps->j++] = '/';
	while (ps->k < ps->cmd_len)
	{
		ps->full_path[ps->j + ps->k] = cmd[ps->k];
		ps->k++;
	}
	ps->full_path[ps->j + ps->k] = '\0';
}

void	free_paths_array(char **paths)
{
	(void)paths;
}

int	pipe_number(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}
