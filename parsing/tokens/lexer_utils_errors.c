/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:04:43 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 00:09:44 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_operator_error(char *line, int j)
{
	if (line[j] == '<' && line[j + 1] == '<')
		printf("minishell: syntax error near unexpected token `<<'\n");
	else if (line[j] == '>' && line[j + 1] == '>')
		printf("minishell: syntax error near unexpected token `>>'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", line[j]);
}

int	check_consecutive_operators(char *line, int i)
{
	int	j;

	if (!(line[i] == '|' || line[i] == '>' || line[i] == '<'))
		return (0);
	j = i + 1;
	if ((line[i] == '>' && line[j] == '>') || (line[i] == '<'
			&& line[j] == '<'))
		j++;
	while (line[j] == ' ')
		j++;
	if (line[j] == '|' || line[j] == '>' || line[j] == '<')
	{
		print_operator_error(line, j);
		return (1);
	}
	if (line[j] == '\0' || line[j] == '\n')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

void	print_error(void)
{
	printf("minishell: syntax error: unclosed quote\n");
	g_exit_status = 2;
}

void	skip_space(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
