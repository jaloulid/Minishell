/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:27:53 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:25 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_env(char *str, t_node *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
