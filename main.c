/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:39:56 by jaloulid          #+#    #+#             */
/*   Updated: 2025/08/10 17:31:53 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static int	process_command_line(char *line, t_node **env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return (handle_empty_tokens(line));
	cmds = parse_tokens(tokens);
	if (!cmds)
		return (0);
	execute_commands(cmds, env);
	return (1);
}

static int	handle_input_line(char *line, t_node **env)
{
	int	result;
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (0);
	}
	add_history(line);
	result = process_command_line(line, env);
	free(line);
	if (result == -1)
		return (-1);
	return (1);
}

static int	run_command_loop(t_node *env)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		result = handle_input_line(line, &env);
		if (result == -1)
			return (1);
	}
	return (g_exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_node		*env;
	int			result;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	env = env_init(envp);
	result = run_command_loop(env);
	alloc(0, FREE);
	return (result);
}
