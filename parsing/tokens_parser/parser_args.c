/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:45:40 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/07 00:46:56 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_value(char *value)
{
	int	i;

	i = 0;
	while (value[i] && (value[i] == ' ' || value[i] == '\t'
			|| value[i] == '\n'))
		i++;
	return (!value[i]);
}

static char	**create_new_args(t_cmd *cmd, char *value)
{
	char	**new_args;
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = alloc(sizeof(char *) * (i + 2), ALLOC);
	if (!new_args)
		return (NULL);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i++] = ft_strdup(value);
	new_args[i] = NULL;
	return (new_args);
}

void	collect_arg(t_cmd *cmd, char *value)
{
	char	**new_args;

	if (!cmd || !value || !*value)
		return ;
	if (is_empty_value(value))
		return ;
	new_args = create_new_args(cmd, value);
	if (!new_args)
		return ;
	cmd->args = new_args;
}

void	parse_word_token(t_token **tokens, t_cmd *cmd)
{
	if ((*tokens)->type == WORD && cmd)
		collect_arg(cmd, (*tokens)->value);
}
