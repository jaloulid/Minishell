/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:41:03 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/10 17:43:44 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = alloc(sizeof(t_token), ALLOC);
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->quoted = 0;
	token->next = NULL;
	return (token);
}

void	add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token_type	get_token_type(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(s, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (REDIR_OUT);
	return (WORD);
}
