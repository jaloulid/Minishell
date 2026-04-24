/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:39:07 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/11 00:59:48 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote(char *str, int *i, int *in_quotes, char *quote_char)
{
	if ((str[*i] == '"' || str[*i] == '\'') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = str[*i];
		(*i)++;
	}
	else if (str[*i] == *quote_char && *in_quotes)
	{
		*in_quotes = 0;
		*quote_char = 0;
		(*i)++;
	}
}

static char	*handle_dollar(char *str, int *i, t_node *env, int last_exit)
{
	char	*tmp;

	(*i)++;
	tmp = expand_dollar(str, i, env, last_exit);
	return (tmp);
}

char	*expand_var(char *str, t_node *env, int last_exit)
{
	char	*res;
	int		i;
	int		in_quotes;
	char	quote_char;

	res = ft_strdup("");
	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && (!in_quotes
				|| str[i] == quote_char))
			handle_quote(str, &i, &in_quotes, &quote_char);
		else if (str[i] == '$' && (!in_quotes || quote_char == '"'))
			res = append_str(res, handle_dollar(str, &i, env, last_exit));
		else
			res = append_char(res, str[i++]);
	}
	return (res);
}

char	*remove_empty_quotes(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}
