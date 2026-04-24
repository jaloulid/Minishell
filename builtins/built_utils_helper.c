/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:00:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 19:29:45 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_env_nodes(t_node *a, t_node *b)
{
	char	*tmp_key;
	char	*tmp_val;
	int		tmp_to_print;

	tmp_key = a->key;
	tmp_val = a->value;
	tmp_to_print = a->to_print;
	a->key = b->key;
	a->value = b->value;
	a->to_print = b->to_print;
	b->key = tmp_key;
	b->value = tmp_val;
	b->to_print = tmp_to_print;
}

int	ft_strcmp(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] && dest[i] && (src[i] == dest[i]))
		i++;
	return (src[i] - dest[i]);
}

t_node	*return_address(char *str, t_node **env)
{
	t_node	*looper;

	looper = (*env);
	while (looper && looper->key != str)
		looper = looper->next;
	return (looper);
}

int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

void	print_sorted_env(t_node *ptr)
{
	while (ptr)
	{
		if (ptr->key)
		{
			if (ptr->value && ptr->to_print)
				printf("declare -x %s=\"%s\"\n", ptr->key, ptr->value);
			else
				printf("declare -x %s\n", ptr->key);
		}
		ptr = ptr->next;
	}
}
