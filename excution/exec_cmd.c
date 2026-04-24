/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:32:18 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 17:41:24 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_external(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		result;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		return (-1);
	}
	else if (pid == 0)
		handle_child_process(cmd, env);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		result = handle_parent_process(pid);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		return (result);
	}
	return (0);
}

int	exec_cmd(t_cmd *arg, t_node **env)
{
	char	**env_array;
	int		result;

	if (!arg->args || !arg->args[0] || ft_strlen(arg->args[0]) == 0)
	{
		if (arg->redirect)
		{
			if (handle_redirects(arg, *env, g_exit_status) == -1)
				return (1);
			return (0);
		}
		ft_putstr_fd("minishell: ", 2);
		if (arg->args && arg->args[0])
			ft_putstr_fd(arg->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		g_exit_status = 127;
		return (127);
	}
	if (is_builtin(arg->args[0]))
		return (run_builtin(arg, env, arg->args));
	if (validate_external_command(arg->args, env) == -1)
		return (127);
	env_array = env_list_to_array(env);
	result = exec_external(arg, env_array);
	return (result);
}
