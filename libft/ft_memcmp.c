/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:19:20 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/11 15:50:04 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	if (n == 0)
		return (0);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((i < n - 1) && p1[i] == p2[i])
		i++;
	return (p1[i] - p2[i]);
}
/*
int main()
{
	char *p = "youssef";
	char *l = "yousef";
	int n = ft_memcmp(p, NULL, 0);
	int k = memcmp(p, NULL, 0);
	printf("%d\n%d\n", n, k);
}
*/
