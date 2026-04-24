/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:10:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:25 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cd_path(char *command, t_node *env)
{
	char	*path;

	if (command == NULL)
	{
		path = get_env_value(env, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		path = command;
	return (path);
}

void	update_pwd_env(t_node **env, char *current_pwd)
{
	char	*new_pwd;

	if (current_pwd)
		set_env_value(env, "OLDPWD", current_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_value(env, "PWD", new_pwd);
		free(new_pwd);
	}
}
