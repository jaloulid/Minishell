NAME = minishell

SRC = main.c main_helper.c G-C/g_c.c parsing/tokens/lexer.c parsing/tokens/lexer_word.c parsing/tokens/lexer_utils.c parsing/tokens_parser/parser_utils.c \
parsing/tokens_parser/parser_args.c parsing/tokens_parser/parce_redir.c parsing/tokens_parser/parser_utils2.c parsing/env/env_helper.c parsing/tokens_parser/parser_tokens.c parsing/tokens/lexer_errors.c parsing/tokens/lexer_utils_errors.c\
parsing/expand/expand_dollar.c parsing/expand/expand_var.c parsing/expand/expand_var_heredoc.c parsing/expand/expand_utils.c parsing/expand/expand_cmd.c\
builtins/built_utils.c builtins/built_utils_helper.c builtins/env_utils.c builtins/env_utils_helper.c builtins/sort_env.c \
builtins/env_init_helper.c builtins/ft_cd_helper.c \
builtins/exit.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c \
excution/exec_cmd.c excution/exec_cmd_helper.c excution/exec_utils.c excution/exec_utils_helper.c excution/exec_builtin.c excution/find_paths.c \
pipes/pipe_handle.c pipes/pipe_handle_helper.c pipes/pipe_handle_helper2.c \
herdoc/handle_files.c herdoc/handle_files_helper.c herdoc/heredoc_utils.c herdoc/herdoc.c herdoc/herdoc_helper.c \
herdoc/herdoc_input.c herdoc/herdoc_multi.c herdoc/herdoc_pipe.c signals/handle_signals.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS =  -Wall -Werror -Wextra -g -fPIE 

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I.

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
