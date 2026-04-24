/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:59:55 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 19:29:45 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_exit_arg(char *arg)
{
	if (!arg)
		return (1);
	return (only_digit(arg));
}

static int	calculate_exit_status(char *arg)
{
	int	status;

	status = ft_atoi(arg);
	return (status & 255);
}

int	ft_exit(char **av, t_node **env)
{
	int	exit_status;

	(void)env;
	printf("exit\n");
	if (av[1] == NULL)
	{
		alloc(0, FREE);
		exit(g_exit_status);
	}
	if (validate_exit_arg(av[1]) == 0)
	{
		write(STDERR_FILENO, "exit: ", 6);
		write(STDERR_FILENO, av[1], ft_strlen(av[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		alloc(0, FREE);
		exit(2);
	}
	exit_status = calculate_exit_status(av[1]);
	alloc(0, FREE);
	exit(exit_status);
}
