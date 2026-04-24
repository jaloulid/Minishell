/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:40:55 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:25 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *command, t_node **env)
{
	char	*path;
	char	*current_pwd;

	current_pwd = get_env_value(*env, "PWD");
	path = get_cd_path(command, *env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd_env(env, current_pwd);
	return (0);
}
