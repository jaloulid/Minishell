/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:13:51 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/02 16:52:28 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rex;
	size_t	com;

	if (size != 0 && count > (size_t) - 1 / size)
		return (NULL);
	com = size * count;
	rex = alloc(com, ALLOC);
	if (!rex)
		return (NULL);
	if (com == 0)
		com = 1;
	ft_memset(rex, 0, com);
	return (rex);
}
