/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:45:02 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/10 17:43:33 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_operator_at_start(char *line, int i)
{
	int	start;

	if (i == 0 || (i > 0 && line[i - 1] == ' '))
	{
		start = 0;
		while (line[start] == ' ')
			start++;
		if (start == i && line[i] == '|')
		{
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
	}
	return (0);
}

static int	check_triple_operators(char *line, int i)
{
	if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
		|| (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		|| (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|'))
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

static int	check_mixed_redirections(char *line, int i)
{
	if ((line[i] == '<' && line[i + 1] == '>') || (line[i] == '>' && line[i
				+ 1] == '<'))
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

static int	check_unsupported_operators(char *line, int i)
{
	if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == '&' && line[i
				+ 1] == '&') || (line[i] == '/' && line[i + 1] == '/')
		|| (line[i] == '\\' && line[i + 1] == '\\'))
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	check_invalid_syntax(char *line, int i)
{
	if (check_operator_at_start(line, i))
		return (1);
	if (check_triple_operators(line, i))
		return (1);
	if (check_mixed_redirections(line, i))
		return (1);
	if (check_unsupported_operators(line, i))
		return (1);
	if (check_consecutive_operators(line, i))
		return (1);
	return (0);
}
