/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:45:32 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 16:37:11 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_echo_flags(char **argv, int *i)
{
	int	newline;
	int	k;

	newline = 0;
	k = 0;
	while (argv[*i] && argv[*i][k] == '-')
	{
		k = 1;
		while (argv[*i][k] == 'n')
			k++;
		if (argv[*i][k] == '\0')
		{
			newline = 1;
			(*i)++;
			k = 0;
		}
		else
			break ;
	}
	return (newline);
}

int	ft_echo(char **argv)
{
	int	newline;
	int	i;

	i = 1;
	newline = process_echo_flags(argv, &i);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
