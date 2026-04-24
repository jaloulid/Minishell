/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:43:27 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/10 18:32:06 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_assignment_export(char *key, char *value, t_node **env)
{
	t_node	*current;

	current = *env;
	while (current && ft_strcmp(key, current->key) != 0)
		current = current->next;
	if (current)
	{
		current->value = ft_strdup(value);
		current->to_print = 1;
	}
	else
		env_add_back(env, env_add_new(key, value));
}

static void	handle_no_assignment_export(char *arg, t_node **env)
{
	t_node	*current;

	current = *env;
	while (current && ft_strcmp(arg, current->key) != 0)
		current = current->next;
	if (!current)
		env_add_back(env, (current = env_add_new(arg, ""),
				current->to_print = 0, current));
}

static int	process_export_arg(char *arg, t_node **env)
{
	char	*found;
	char	*key;
	char	*value;

	found = ft_strchr(arg, '=');
	if (found)
	{
		key = ft_substr(arg, 0, found - arg);
		value = found + 1;
		handle_assignment_export(key, value, env);
	}
	else
		handle_no_assignment_export(arg, env);
	return (0);
}

static int	validate_identifier(char *arg)
{
	int	j;

	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	j = 1;
	while (arg[j] && arg[j] != '=' && (ft_isalnum(arg[j]) || arg[j] == '_'))
		j++;
	if (arg[j] && arg[j] != '=')
		return (0);
	return (1);
}

int	ft_export(char **av, t_node **env)
{
	int	i;
	int	ret_status;

	if (!av[1])
		return (env_sort(env));
	ret_status = 0;
	i = 1;
	while (av[i])
	{
		if (!validate_identifier(av[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", av[i]);
			ret_status = 1;
		}
		else if (process_export_arg(av[i], env) != 0)
			ret_status = 1;
		i++;
	}
	return (ret_status);
}
