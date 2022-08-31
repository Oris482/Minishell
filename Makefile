# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/20 15:48:55 by jaesjeon          #+#    #+#              #
#    Updated: 2022/08/31 16:05:21 by jaesjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
# CFLAGS 		=	-Wall -Wextra -Werror $(CPPFLAGS) # -fsanitize=address
# CFLAGS 		=	-Wall -Wextra -Werror $(CPPFLAGS)
# CFLAGS 		=	-Wall -Wextra -Werror
CFLAGS			= 	-fsanitize=address

LINKER		=	$(LDFLAGS) -lreadline
COMPILE		=	-c $(CPPFLAGS)
RM 			=	rm -vf
AR 			= ar
MAKE_C 		= make -C

MY_FUNC_DIR		=	my_func/
LINER_DIR 		=	liner/
LEXER_DIR 		=	lexer/
PARCER_DIR		=	parcer/
EXCUTER_DIR		=	excuter/

NAME	 	=	minishellw

# 파일 기능별로 분류해서 소스파일 넣기

MY_FUNC_SRCS		=	about_alloc.c	\
						about_dir.c		\
						about_pipe.c

LINER_SRCS			= 	liner.c 		

LEXER_SRCS			=	lexer.c							\
						check_char_utils.c				\
						check_interpret_symbol_utils.c	\
						tokenization_utils.c			\
						interpreter.c					\
						interpreter_middleware.c		\
						interpreter_make_chunk.c		\
						compress_target_char.c			\
						wildcard_traslator.c			\
						dirent_utils.c					\
						find_files.c

MANDA_SRCS	=	minishell.c									\
				minishell_utils.c							\
				origin_str_utils.c							\
				custom_str_utils.c							\
				terminal_setting.c							\
				$(addprefix $(MY_FUNC_DIR), $(MY_FUNC_SRCS))	\
				$(addprefix $(LINER_DIR), $(LINER_SRCS))	\
				$(addprefix $(LEXER_DIR), $(LEXER_SRCS))



# SRCS			= 	$(MANDA_SRCS)
# HADS			=	$(MANDATORY_DIR)push_swap.h
OBJS			=	$(MANDA_SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LINKER) -I$(LEXER_DIR) -o $@
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@echo ">>>>>>>>>> Minishell Compiled! <<<<<<<<<<"
	@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%.o: %.c
	@echo [$<] compiling...
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(MY_FUNC_DIR) -I$(LEXER_DIR) -I. $(COMPILE) $< -o $@

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
	"OBJS			=	$(BONUS_SRCS:.c=.o))"							\

list:
	@echo $(MANDA_SRCS)
	@echo $(OBJS)

lldb:
	$(CC) $(CFLAGS) $(MANDA_SRCS) $(LINKER) -I$(MY_FUNC_DIR) -I$(LEXER_DIR) -I. $(CPPFLAGS) -o $(NAME) -g
	cp minishell lexer/test_dir/

.PHONY: all clean fclean re bonus
