/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:52:36 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 16:55:16 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "g_c.h"

void	free_garbage(t_garbage **garbage)
{
	t_garbage	*temp;
	t_garbage	*current;
	int			count;

	count = 0;
	if (!garbage || !*garbage)
		return ;
	current = *garbage;
	while (current)
	{
		temp = current;
		current = current->next;
		count++;
		if (temp->ptr && temp->ptr != NULL)
			free(temp->ptr);
		free(temp);
	}
	*garbage = NULL;
}

t_garbage	*new_garbage(void *allocated)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (write(2, "malloc failure\n", 15), NULL);
	new->ptr = allocated;
	new->next = NULL;
	return (new);
}

void	garbage_add_back(void *allocated, t_garbage **garbage)
{
	t_garbage	*last;
	t_garbage	*new_allocation;

	if (!garbage)
		return ;
	new_allocation = new_garbage(allocated);
	if (!new_allocation)
		return (free(allocated));
	if (!*garbage)
	{
		*garbage = new_allocation;
		return ;
	}
	last = *garbage;
	while (last->next)
		last = last->next;
	if (last)
		last->next = new_allocation;
}

void	*alloc(size_t size, t_action action)
{
	void				*returned;
	static t_garbage	*garbage;

	if (action == ALLOC)
	{
		returned = malloc(size);
		if (!returned)
			return (write(2, "malloc failure\n", 15), NULL);
		garbage_add_back(returned, &garbage);
		return (returned);
	}
	else if (action == FREE)
	{
		if (garbage != NULL)
		{
			free_garbage(&garbage);
			garbage = NULL;
		}
	}
	return (NULL);
}
