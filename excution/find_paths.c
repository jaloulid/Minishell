/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:27:46 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 16:49:29 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_paths(char **env)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	paths = NULL;
	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	char	*temp_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		i++;
	}
	return (NULL);
}

char	*check_path(char *cmd, t_node **env)
{
	char	**env_array;
	char	**paths;
	char	*result;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	env_array = env_list_to_array(env);
	paths = find_paths(env_array);
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	return (result);
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
