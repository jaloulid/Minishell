/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:21:53 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/11 14:59:15 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	char	b;
	int		j;

	b = (char)i;
	j = 0;
	while (s[j])
	{
		if (s[j] == b)
			return ((char *)(s + j));
		j++;
	}
	if (b == '\0')
		return ((char *)(s + j));
	return (0);
}
