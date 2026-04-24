/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:01:28 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:25 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_sort(t_node **env)
{
	int		swapped;
	t_node	*ptr;

	swapped = 1;
	if (!env || !(*env))
		return (0);
	while (swapped)
	{
		swapped = 0;
		ptr = *env;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_env_nodes(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
	print_sorted_env(*env);
	return (0);
}
