# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/20 15:48:55 by jaesjeon          #+#    #+#              #
#    Updated: 2022/09/17 05:45:38 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
# CFLAGS 		=	-Wall -Wextra -Werror $(CPPFLAGS) # -fsanitize=address
# CFLAGS 		=	-Wall -Wextra -Werror $(CPPFLAGS)
CFLAGS			= 	-fsanitize=address
# CFLAGS 		=	-Wall -Wextra -Werror

LINKER		=	$(LDFLAGS) -lreadline
COMPILE		=	-c
RM 			=	rm -vf
AR 			= ar
MAKE_C 		= make -C

MY_FUNC_DIR		=	myfunc/
LINER_DIR 		=	liner/
LEXER_DIR 		=	lexer/
PARSER_DIR		=	parser/
EXECUTOR_DIR	=	executor/

NAME	 	=	minishell

# 파일 기능별로 분류해서 소스파일 넣기
MY_FUNC_SRCS		=	about_alloc.c		\
						about_dir.c			\
						about_readline.c	\
						about_env.c			\
						about_pipe.c

LINER_SRCS			= 	liner.c

LEXER_SRCS			=	lexer.c							\
						debug_function.c				\
						check_char_utils.c				\
						check_interpret_symbol_utils.c	\
						tokenization_utils.c			\
						interpreter.c					\
						interpreter_middleware.c		\
						interpreter_make_chunk.c		\
						compress_target_char.c			\
						wildcard_translator.c			\
						dirent_utils.c					\
						find_files.c					\
						make_node.c						\
						check_syntax_error.c			\
						find_files_utils.c

PARSER_SRCS			=	parser.c						\
						print_tree.c					\
						tree_utils.c

EXECUTOR_SRCS		=	executor.c						\
						redirections.c					\
						builtin_echo.c					\
						builtin_cd.c					\
						builtin_pwd.c					\
						builtin_export.c				\
						builtin_env.c					\
						builtin_unset.c					\
						builtin_exit.c					\
						program.c

MANDA_SRCS	=	minishell.c										\
				minishell_utils.c								\
				origin_str_utils.c								\
				origin_str_utils2.c								\
				origin_putfd_utils.c							\
				custom_str_utils.c								\
				custom_str_utils2.c								\
				terminal_setting.c								\
				error_utils.c									\
				free_utils.c									\
				linked_list_utils.c								\
				exit_status.c									\
				envp_utils.c									\
				dict_utils.c									\
				debug_print_envp.c								\
				$(addprefix $(MY_FUNC_DIR), $(MY_FUNC_SRCS))	\
				$(addprefix $(LINER_DIR), $(LINER_SRCS))		\
				$(addprefix $(LEXER_DIR), $(LEXER_SRCS))		\
				$(addprefix $(PARSER_DIR), $(PARSER_SRCS))		\
				$(addprefix $(EXECUTOR_DIR), $(EXECUTOR_SRCS))



# SRCS			= 	$(MANDA_SRCS)
# HADS			=	$(MANDATORY_DIR)push_swap.h
OBJS			=	$(MANDA_SRCS:.c=.o)
INC_HEADERS		=	-I. -I$(MY_FUNC_DIR) -I$(LINER_DIR) -I$(LEXER_DIR) -I$(PARSER_DIR) $(CPPFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LINKER) -I$(LEXER_DIR) -o $@
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

bonus:
	@$(MAKE) \
	"NAME 			=	$(BONUS_NAME)"									\
	"OBJS			=	$(BONUS_SRCS:.c=.o)"							\

list:
	@echo $(MANDA_SRCS)
	@echo $(OBJS)

lldb:
	$(CC) $(CFLAGS) $(MANDA_SRCS) $(LINKER) $(INC_HEADERS) $(CPPFLAGS) -o $(NAME) -g

gdb:
	gcc $(CFLAGS) $(MANDA_SRCS) $(LINKER) $(INC_HEADERS) $(CPPFLAGS) -o $(NAME) -g

.PHONY: all clean fclean re bonus
