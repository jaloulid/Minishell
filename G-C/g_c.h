/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_c.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:53:38 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 16:55:04 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_C_H
# define G_C_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_action
{
	ALLOC,
	FREE
}						t_action;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

void					*alloc(size_t size, t_action action);

#endif
