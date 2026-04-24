/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:53:08 by yoessedr          #+#    #+#             */
/*   Updated: 2024/11/13 14:08:56 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(int c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && isinset(s[start], set))
		start++;
	end = ft_strlen(s);
	while (end > start && isinset(s[end - 1], set))
		end--;
	return (ft_substr(s, start, end - start));
}
/*
int main()
{
	char const	s[] = "   \n\n\r\r\t\t   HI TRIM THIS \n\n\n string   \t\t\n  ";
	//char const *s = NULL;
	char const *set = NULL;
	//char const	set[] = "\n\t\r ";
	
	char	*trimmed;
	
	trimmed = ft_strtrim(s,set);

	printf("%s\n", trimmed);

	free (trimmed);
}*/