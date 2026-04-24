/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:30:00 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:25 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env_nodes(t_node *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	fill_env_array(char **envp, t_node *tmp)
{
	int	i;
	int	len;

	i = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2;
		envp[i] = alloc(sizeof(char) * len, ALLOC);
		if (!envp[i])
			return ;
		ft_strlcpy(envp[i], tmp->key, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i], tmp->value, len);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
}

char	**env_list_to_array(t_node **env)
{
	t_node	*tmp;
	char	**envp;
	int		count;

	if (!env || !(*env))
		return (NULL);
	tmp = (*env);
	count = count_env_nodes(tmp);
	envp = alloc(sizeof(char *) * (count + 1), ALLOC);
	if (!envp)
		return (NULL);
	fill_env_array(envp, *env);
	return (envp);
}
