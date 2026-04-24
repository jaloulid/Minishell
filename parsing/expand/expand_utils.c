/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:11:45 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/06 23:38:18 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *base, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (append_str(base, tmp));
}

char	*append_str(char *base, char *add)
{
	char	*old_base;

	if (!add)
		return (base);
	old_base = base;
	base = ft_strjoin(base, add);
	(void)old_base;
	return (base);
}
