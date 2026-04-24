/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:19:44 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/11 14:36:05 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*g;
	unsigned char	*b;

	if (!dest && !src)
		return (NULL);
	i = 0;
	g = (unsigned char *)dest;
	b = (unsigned char *)src;
	while (i < n)
	{
		g[i] = b[i];
		i++;
	}
	return (g);
}
/*
int main()
{
	char *b = memcpy(((void *)0), ((void *)0), 3);
	printf("%s\n", b);
}*/
