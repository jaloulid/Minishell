/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:56:40 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/11 00:50:59 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "G-C/g_c.h"
# include "libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 1024
# ifndef REDIRECT_IN
#  define REDIRECT_IN 0
# endif

# ifndef REDIRECT_OUT
#  define REDIRECT_OUT 1
# endif

extern int			g_exit_status;

typedef struct s_node
{
	char			*key;
	char			*value;
	int				to_print;
	struct s_node	*next;
}					t_node;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
}					t_token;

// lexer functions
t_token				*lexer(char *line);
t_token				*new_token(char *value, t_token_type type);
void				add_back(t_token **list, t_token *new);
t_token_type		get_token_type(char *s);
int					get_word_len(char *line);
int					handle_word(char *line, int *i, t_token **list);
void				handle_operator(char *line, int *i, t_token **list);
int					check_invalid_syntax(char *line, int i);
int					check_consecutive_operators(char *line, int i);
void				print_error(void);
void				skip_space(char *line, int *i);
int					is_operator(char c);

// PARSER STRUCTER
typedef enum e_redir_type
{
	// REDIR_IN,
	// REDIR_OUT,
	// REDIR_APPEND,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}					t_redir_type;

typedef enum e_file_mode
{
	READ_MODE,
	WRITE_TRUNC_MODE,
	WRITE_APPEND_MODE
}					t_file_mode;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	int				quoted_delimiter;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirect;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_fd
{
	int				in_fd;
	int				out_fd;
}					t_fd;
int					ft_echo(char **argv);
int					ft_cd(char *command, t_node **env);
int					ft_pwd(char **av);
t_node				*env_init(char **env);
int					ft_unset(t_node **env, char *c_name);
void				env_add_back(t_node **env, t_node *new);
t_node				*env_add_new(char *key, char *value);
int					env_sort(t_node **env);
int					ft_strcmp(char *src, char *dest);
t_node				*return_address(char *str, t_node **env);
int					only_digit(char *str);
int					ft_export(char **av, t_node **env);
int					exec_external(t_cmd *cmd, char **env);
int					is_builtin(char *cmd);
int					exec_cmd(t_cmd *arg, t_node **env);
int					exec_builtin(char **cmd, t_node **env);
char				**find_paths(char **env);
char				*check_path(char *cmd, t_node **env);
int					ft_exit(char **av, t_node **env);
int					ft_env(t_node *env);
int					ft_search_env(char *str, t_node *env);
int					exec_pipes(t_cmd *cmds, t_node **env);
int					pipe_number(t_cmd *cmds);
void				swap_env_nodes(t_node *a, t_node *b);
int					exec_pipe(t_cmd *cmds, t_node **env);
t_cmd				*parse_tokens(t_token *tokens);
void				expand_cmds(t_cmd *cmds, t_node *env, int status);
t_cmd				*new_cmd(void);
char				*get_env_value(t_node *env, char *key);
void				set_env_value(t_node **env, char *key, char *value);
char				**env_list_to_array(t_node **env);
char				*get_next_line(int fd);
int					open_filee(char *filename, t_file_mode mode);
int					handle_files(t_redir *file, t_node *env, int status);
int					open_file(const char *filename, int flags);
int					close_file(int fd);
int					redirect_file(int fd, int mode);
t_redir				*find_last_heredoc(t_redir *file);
int					process_single_heredoc(t_redir *redirect,
						t_redir *last_heredoc, t_node *env, int status);
int					handle_multiple_heredocs(t_redir *file,
						t_node *env, int status);
int					handle_heredoc(const char *delimiter,
						t_node *env, int status);
char				*read_line_from_stdin(void);
int					is_delimiter_match(const char *line, const char *delimiter,
						size_t delimiter_len);
char				*append_line_to_content(char *content, char *line);
char				*init_heredoc_content(void);
int					process_heredoc_line(char *line, const char *delimiter,
						size_t delimiter_len, int is_terminal);
int					create_heredoc_pipe(int *pipefd);
int					write_heredoc_content(char *content, int write_fd);
char				*read_heredoc_line(int is_terminal);
int					check_heredoc_termination(char *line, const char *delimiter,
						size_t delimiter_len, int is_terminal);
int					setup_heredoc_pipe_and_signals(int *pipefd);
void				cleanup_heredoc(char *content, int *pipefd);
t_redir				*new_redir(char *file, t_redir_type type);
char				*append_char(char *base, char c);
void				redir_add_back(t_redir **lst, t_redir *new);
char				*expand_dollar(const char *str, int *i, t_node *env,
						int last_exit);
void				cmd_add_back(t_cmd **lst, t_cmd *new);
char				*append_str(char *base, char *add);
char				*expand_var(char *str, t_node *env, int last_exit);
char				*expand_var_heredoc(char *str, t_node *env, int last_exit);
char				*remove_empty_quotes(char *str);
int					parse_one_token(t_token *tokens, t_cmd **current,
						t_cmd **cmds);
void				parse_init_cmd(t_cmd **current, t_cmd **cmds);
void				parse_handle_pipe(t_cmd **current);
void				parse_word_token(t_token **tokens, t_cmd *cmd);
int					is_redirect(t_token *token);
int					check_pipe_syntax(t_token *tokens);
int					parse_redirect_token(t_token **tokens, t_cmd *cmd);
int					redirect_file(int fd, int mode);
void				sigint_handler(int sig);
void				heredoc_sigint_handler(int sig);
void				child_sigint_handler(int sig);
void				ctrl_d_handle(void);
int					handle_redirects(t_cmd *arg, t_node *env, int status);
int					handle_file_error(char *filename, int error_code);

int					validate_external_command(char **args, t_node **env);
int					run_builtin(t_cmd *cmd, t_node **env, char **args);

void				print_sorted_env(t_node *ptr);
void				fill_env_array(char **envp, t_node *tmp);
int					count_env_nodes(t_node *env);

void				process_env_entry(char *env_entry, t_node **head);
char				*get_cd_path(char *command, t_node *env);
void				update_pwd_env(t_node **env, char *current_pwd);
int					handle_parent_process(pid_t pid);
int					check_command_existence(char *cmd);
int					check_file_existence(char *path);
int					check_file_permission(char *path);
int					check_is_directory(char *path);
int					handle_child_process(t_cmd *cmd, char **env);

typedef struct s_pipe_info
{
	t_cmd	*cmds;
	int		input_fd;
	int		has_pipe;
	int		*pipe_fd;
	t_node	**env;
}	t_pipe_info;

int					setup_pipe(int *pipe_fd);
void				child_process(t_pipe_info info);
void				parent_process_no_wait(int *input_fd,
						int has_pipe, int *pipe_fd);
void				parent_process(pid_t pid, int *input_fd, int has_pipe,
						int *pipe_fd);
// pipe_handle_helper2 functions
void				handle_pipe_cleanup(int *input_fd, int has_pipe,
						int *pipe_fd);
void				handle_exit_status(int status, int is_last_cmd);

// main_helper functions
int					handle_empty_tokens(char *line);
void				execute_commands(t_cmd *cmds, t_node **env);

#endif
