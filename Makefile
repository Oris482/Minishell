# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/20 15:48:55 by jaesjeon          #+#    #+#              #
#    Updated: 2022/09/27 10:58:56 by jaesjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror

COMPILE		=	-c
RM 			=	rm -rvf
AR 			= ar
MAKE_C 		= make -C

BREW_DIR		:= $(shell brew --prefix readline)
READLINE_LIB	:= $(addprefix $(BREW_DIR)/, lib)
READLINE_INC	:= -I $(addprefix $(BREW_DIR)/, include)
READLINE_LIB	:= -lreadline -L$(READLINE_LIB)

# FT_DEBUG_DIR 		=	ft_debug/
FT_ALLOC_DIR		=	ft_alloc/
FT_CHECK_DIR		=	ft_check/
FT_COMMAND_DIR		=	ft_command/
FT_ENVIRON_DIR		=	ft_environ/
FT_FILE_DIR			=	ft_file/
FT_LIBRARY_DIR		=	ft_library/
FT_PRINT_DIR 		=	ft_print/
FT_STRING_DIR 		=	ft_string/
FT_TOKEN_DIR 		=	ft_token/
FT_TREE_DIR			=	ft_tree/

NAME	 	=	minishell

# FT_DEBUG_SRCS	=	debug_function.c				\
					debug_print_envp.c				\
					debug_print_tree.c
FT_ALLOC_SRCS	=	about_alloc.c					\
					free_utils.c
FT_CHECK_SRCS	=	check_char_utils.c				\
					check_special_char_utils.c		\
					check_env_utils.c				\
					check_interpret_symbol_utils.c
FT_COMMAND_SRCS	=	builtin_cd.c					\
					builtin_exit.c					\
					builtin_handle_env.c			\
					print_env.c						\
					program.c						\
					builtin_echo.c					\
					builtin_pwd.c					\
					about_pipe.c					\
					pipe_utils.c					\
					redirections.c					\
					heredoc.c						\
					heredoc_utils.c					\
					allow_about_pipe_func.c			\
					builtin_utils.c
FT_ENVIRON_SRCS	=	about_env.c						\
					dict_utils.c					\
					dict_list_utils.c				\
					dict_node_utils.c
FT_FILE_SRCS	=	about_dir.c						\
					dirent_utils.c					\
					find_files.c					\
					find_files_utils.c
FT_LIBRARY_SRCS	=	ft_atoi.c						\
					ft_itoa.c						\
					ft_memset.c
FT_PRINT_SRCS	=	origin_putfd_utils.c			\
					print_error_utils.c
FT_STRING_SRCS	=	custom_str_utils.c				\
					custom_str_utils2.c				\
					origin_str_utils.c				\
					origin_str_utils2.c				\
					get_next_line.c					\
					get_next_line_utils.c
FT_TOKEN_SRCS	=	interpreter.c					\
					token_node_utils.c				\
					token_list_utils.c				\
					quote_tilde_translator.c		\
					dollar_translator.c				\
					dollar_translator_utils.c		\
					wildcard_translator_bonus.c		\
					tokenization_utils.c
FT_TREE_SRCS	=	tree_utils.c

MANDA_SRCS	=	minishell.c											\
				terminal_setting.c									\
				exit_status.c										\
				about_readline.c									\
				liner.c												\
				lexer.c												\
				check_syntax_error.c								\
				check_syntax_middleware.c							\
				parser.c											\
				parser_utils.c										\
				expand_cmd_tree_utils.c								\
				executor.c
MANDA_SRCS	+=	$(addprefix $(FT_ALLOC_DIR), $(FT_ALLOC_SRCS))		\
				$(addprefix $(FT_CHECK_DIR), $(FT_CHECK_SRCS))		\
				$(addprefix $(FT_COMMAND_DIR), $(FT_COMMAND_SRCS))	\
				$(addprefix $(FT_ENVIRON_DIR), $(FT_ENVIRON_SRCS))	\
				$(addprefix $(FT_FILE_DIR), $(FT_FILE_SRCS))		\
				$(addprefix $(FT_LIBRARY_DIR), $(FT_LIBRARY_SRCS))	\
				$(addprefix $(FT_PRINT_DIR), $(FT_PRINT_SRCS))		\
				$(addprefix $(FT_STRING_DIR), $(FT_STRING_SRCS))	\
				$(addprefix $(FT_TOKEN_DIR), $(FT_TOKEN_SRCS))		\
				$(addprefix $(FT_TREE_DIR), $(FT_TREE_SRCS))
#				$(addprefix $(FT_DEBUG_DIR), $(FT_DEBUG_SRCS))		\

OBJS			=	$(MANDA_SRCS:.c=.o)
INC_HEADERS		=	-I. 				\
					$(READLINE_INC)		\
					-I$(FT_ALLOC_DIR)	\
					-I$(FT_CHECK_DIR)	\
					-I$(FT_COMMAND_DIR)	\
					-I$(FT_ENVIRON_DIR)	\
					-I$(FT_FILE_DIR)	\
					-I$(FT_LIBRARY_DIR)	\
					-I$(FT_PRINT_DIR)	\
					-I$(FT_STRING_DIR)	\
					-I$(FT_TOKEN_DIR)	\
					-I$(FT_TREE_DIR)
#					-I$(FT_DEBUG_DIR)	\

all: $(NAME)

$(NAME): $(OBJS)
	@echo [$@] linking...
	@$(CC) $(CFLAGS) $^ $(READLINE_LIB) -o $@
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@echo ">>>>>>>>>> Minishell Compiled! <<<<<<<<<<"
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%.o: %.c
	@echo [$<] compiling...
	@$(CC) $(CFLAGS) $(INC_HEADERS) $(COMPILE) $< -o $@

clean:
	@echo
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(MANDA_SRCS:.c=.o)
	@echo

fclean: clean
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(NAME)
	@$(RM) *.dSYM
	@echo

re:
	@make fclean
	@make all

bonus: all

lldb:
	$(CC) $(CFLAGS) $(MANDA_SRCS) $(INC_HEADERS) $(READLINE_LIB) -o $(NAME) -g

.PHONY: all clean fclean re bonus
