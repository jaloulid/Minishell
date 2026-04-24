/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:20:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 17:22:56 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command_existence(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	g_exit_status = 127;
	return (-1);
}

int	check_file_existence(char *path)
{
	ft_putstr_fd("No such file or directory: ", 2);
	ft_putendl_fd(path, 2);
	g_exit_status = 127;
	return (-1);
}

int	check_file_permission(char *path)
{
	ft_putstr_fd("Permission denied: ", 2);
	ft_putendl_fd(path, 2);
	g_exit_status = 126;
	return (-1);
}

int	check_is_directory(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Is a directory", 2);
	g_exit_status = 126;
	return (-1);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"));
}
