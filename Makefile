# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/20 15:48:55 by jaesjeon          #+#    #+#              #
#    Updated: 2022/08/23 18:14:37 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
# CFLAGS 		=	-Wall -Wextra -Werror $(CPPFLAGS) # -fsanitize=address
# CFLAGS 		=	-Wall -Wextra -Werror $(CPPFLAGS)
CFLAGS 		=	-Wall -Wextra -Werror

LINKER		=	$(LDFLAGS) -lreadline
COMPILE		=	-c $(CPPFLAGS)
RM 			=	rm -vf
AR 			= ar
MAKE_C 		= make -C

LINER_DIR 		=	liner/
LEXER_DIR 		=	lexer/
PARCER_DIR		=	parcer/
EXCUTER_DIR		=	excuter/

NAME	 	=	minishell

# 파일 기능별로 분류해서 소스파일 넣기
LINER_SRCS			= 	liner.c 		\
						liner_utils.c

LEXER_SRCS			=	lexer.c			\

MANDA_SRCS	=	minishell.c									\
				minishell_utils.c							\
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
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LEXER_DIR) -I. $(COMPILE) $< -o $@

clean:
	@echo
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(MANDA_SRCS:.c=.o)
	@echo

fclean: clean
	@echo ">>>>>>>>>>>>>>>> Delete List <<<<<<<<<<<<<<<<<<<<"
	@$(RM) $(NAME)
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
	$(CC) $(CFLAGS) $(MANDA_SRCS) $(LINKER) -I$(LEXER_DIR) -I. $(CPPFLAGS) -o $(NAME) -g

.PHONY: all clean fclean re bonus
