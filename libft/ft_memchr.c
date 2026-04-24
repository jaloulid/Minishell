/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:51 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/13 14:06:53 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p;
	char	k;

	k = (char)c;
	i = 0;
	p = (char *)s;
	while (i < n)
	{
		if (p[i] == k)
			return (p + i);
		i++;
	}
	return (NULL);
}
