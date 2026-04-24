/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:50:54 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/06 23:17:08 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(const char *str, int *i, t_node *env, int last_exit)
{
	char	*key;
	char	*value;
	char	*result;
	int		start;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_exit));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	value = get_env_value(env, key);
	if (value)
		result = ft_strdup(value);
	else
		result = ft_strdup("");
	return (result);
}
