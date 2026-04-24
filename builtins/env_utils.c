/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:27:37 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 18:03:57 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*env_add_new(char *key, char *value)
{
	t_node	*new_node;

	new_node = alloc(sizeof(t_node), ALLOC);
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (value && *value)
		new_node->to_print = 1;
	else
		new_node->to_print = 0;
	new_node->next = NULL;
	return (new_node);
}

void	env_add_back(t_node **env, t_node *new)
{
	t_node	*tmp;

	if (!env || !new)
		return ;
	tmp = *env;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_node	*env_init(char **env)
{
	t_node	*head;

	head = NULL;
	while (*env)
	{
		process_env_entry(*env, &head);
		env++;
	}
	return (head);
}

void	set_env_value(t_node **env, char *key, char *value)
{
	t_node	*current;

	if (!env || !key)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = ft_strdup(value);
			if (value && *value)
				current->to_print = 1;
			else
				current->to_print = 0;
			return ;
		}
		current = current->next;
	}
	env_add_back(env, env_add_new(key, value));
}
