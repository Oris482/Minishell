# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/20 15:48:55 by jaesjeon          #+#    #+#              #
#    Updated: 2022/09/19 23:09:27 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror #-fsanitize=address

LINKER		=	$(LDFLAGS) -lreadline
COMPILE		=	-c
RM 			=	rm -vf
AR 			= ar
MAKE_C 		= make -C

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
					dict_node_utils.c				\
					envp_utils.c
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
					origin_str_utils2.c
FT_TOKEN_SRCS	=	interpreter.c					\
					interpreter_make_chunk.c		\
					token_node_utils.c				\
					token_list_utils.c				\
					translator.c					\
					translator_utils.c				\
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

OBJS			=	$(MANDA_SRCS:.c=.o)
INC_HEADERS		=	-I. 				\
					$(CPPFLAGS)			\
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

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@echo ">>>>>>>>>> Minishell Compiled! <<<<<<<<<<"
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%.o: %.c
	@echo [$<] compiling...
	$(CC) $(CFLAGS) $(INC_HEADERS) $(COMPILE) $< -o $@

clean:
	@echo
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(MANDA_SRCS:.c=.o)
	@echo

fclean: clean
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(NAME)
	@rm -rvf *.dSYM
	@echo

re:
	@make fclean
	@make all

bonus: all

lldb:
	$(CC) $(CFLAGS) $(MANDA_SRCS) $(LINKER) $(INC_HEADERS) $(CPPFLAGS) -o $(NAME) -g

.PHONY: all clean fclean re bonus
