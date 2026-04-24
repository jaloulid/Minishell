/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:52:05 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/13 14:12:59 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	k = 0;
	if (!needle[k])
		return ((char *)haystack);
	i = ft_strlen(needle);
	if (!haystack[k] || i > len)
		return (NULL);
	while (haystack[k] && k < len)
	{
		i = 0;
		while (needle[i] && haystack[k + i] == needle[i] && (k + i) < len)
			i++;
		if (needle[i] == '\0')
			return ((char *)&haystack[k]);
		k++;
	}
	return (NULL);
}
/*
int main()
{
	char *p = strnstr("youssefi", "youssefessedraoui", 8);
	printf("%s\n", p);
}
*/
