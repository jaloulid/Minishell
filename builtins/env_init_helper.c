/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:05:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:25 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_env_entry(char *env_entry, t_node **head)
{
	char	*found;
	char	*key;
	char	*value;
	t_node	*new_node;
	int		len;

	found = ft_strchr(env_entry, '=');
	len = found - env_entry;
	key = ft_substr(env_entry, 0, len);
	value = ft_strdup(found + 1);
	new_node = env_add_new(key, value);
	env_add_back(head, new_node);
}
