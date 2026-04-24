/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:50:30 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/10 17:45:40 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_operator(char *line, int *i, t_token **list)
{
	char	op[3];
	int		j;

	j = 0;
	op[j++] = line[*i];
	if ((line[*i] == '>' || line[*i] == '<') && line[*i + 1] == line[*i])
		op[j++] = line[++(*i)];
	op[j] = '\0';
	(*i)++;
	add_back(list, new_token(op, get_token_type(op)));
}

static int	skip_quotes(char *str, int i)
{
	char	q;

	q = str[i++];
	while (str[i] && str[i] != q)
		i++;
	if (!str[i])
		return (-1);
	return (i + 1);
}

char	*strip_quotes(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

int	get_word_len(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<'
		&& line[i] != '>')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			j = skip_quotes(line, i);
			if (j == -1)
				return (-1);
			i = j;
		}
		else
			i++;
	}
	return (i);
}

int	handle_word(char *line, int *i, t_token **list)
{
	int		len;
	char	*word;
	int		is_quoted;
	t_token	*token;
	char	quote;

	len = get_word_len(&line[*i]);
	if (len == -1)
		return (-1);
	is_quoted = 0;
	if (len >= 2 && (line[*i] == '\'' || line[*i] == '"'))
	{
		quote = line[*i];
		if (line[*i + len - 1] == quote)
			is_quoted = 1;
	}
	word = ft_substr(line, *i, len);
	token = new_token(word, WORD);
	token->quoted = is_quoted;
	add_back(list, token);
	*i += len;
	return (0);
}
