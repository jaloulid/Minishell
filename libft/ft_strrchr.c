/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:52:41 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/13 14:11:14 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*ptr;
	char	k;

	k = (char)c;
	ptr = (char *)s;
	len = ft_strlen(ptr);
	if (k == '\0')
		return (ptr + len);
	while (len >= 0)
	{
		if (ptr[len] == k)
			return (ptr + len);
		len--;
	}
	return (NULL);
}
