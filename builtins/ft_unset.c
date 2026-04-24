/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:42:28 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 16:43:03 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_node **env, char *c_name)
{
	t_node	*current;
	t_node	*prev;

	if (!env || !*env || !c_name)
		return (1);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, c_name) == 0)
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
