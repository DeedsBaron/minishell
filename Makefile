# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/29 15:52:28 by dbaron            #+#    #+#              #
#    Updated: 2021/06/08 15:15:24 by dbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#-Wall -Wextra -Werror
FLAGS =  -MMD -Wall -Wextra -Werror

LIBFT = ./libs/libft/

LIB = ./libs/libft/libft.a

DIR_S = ./src

DIR_O = ./obj

CC = gcc
SOURCES = 2d_array_utilc.c builtins.c builtins_utils.c envp.c exec_tree.c \
			make_tokens.c minishell.c print.c signals.c utils.c bin_folders.c \
			builtins2.c check_tokens.c error.c free.c make_tree.c preprocess_str.c \
			redirects.c singltones.c utils2.c make_tree_utils.c make_tokens_i.c exec_bin.c

SRCS = $(addprefix $(DIR_S)/,${SOURCES})

OBJS = $(addprefix $(DIR_O)/,${SOURCES:.c=.o})

all: dir lib $(NAME)

dir: 
	@echo "\033[0;32m"
	mkdir -p obj
lib:
	@echo "\033[0;32m"

	make -C $(LIBFT)
	@echo "\033[0;36m"

$(DIR_O)/%.o: $(DIR_S)/%.c
	$(CC) $(FLAGS) -c $< -o $@ -g

$(NAME): $(OBJS)
	@echo "\033[0;35m"
	$(CC) $(FLAGS) $^ -o $@ $(LIB) libs/readline/libhistory.a libs/readline/libreadline.a -ltermcap
	chmod 777 $(NAME)
norm:
	@echo "\033[0;32mnorminette $(DIR_S)/*.c\033[0m"
	@norminette $(DIR_S)/*.c
	@echo "\033[0;32mnorminette includes/*.h\033[0m"
	@norminette includes/*.h
	@echo "\033[0;32mnorminette $(LIBFT)/*.c\033[0m"
	@norminette $(LIBFT)/*.{c,h}
clean:
	@echo "\033[0;33m"
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)

test:
	gcc test.c src/utils.c libs/libft/libft.a
fclean: clean
	@echo "\033[0;33m"
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all lib clean fclean re

-include $(OBJS:.o=.d)
-include $(B_OBJS:.o=.d)