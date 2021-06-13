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
FLAGS =  -MMD

LIBFT = ./libs/libft/

LIB = ./libs/libft/libft.a

DIR_S = ./src

DIR_O = ./obj

CC = gcc

SOURCES = main1.c parser.c utils.c error.c check_tokens.c make_tree.c exec_tree.c

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
	$(CC) $(FLAGS) $^ -o $@ $(LIB) -g
	chmod 777 $(NAME)
norm:
	@echo "\033[0;32mnorminette $(DIR_GS)/*.c\033[0m"
	@norminette $(DIR_GS)/*.c
	@echo "\033[0;32mnorminette $(DIR_BS)/*.c\033[0m"
	@norminette $(DIR_BS)/*.c
	@echo "\033[0;32mnorminette $(DIR_MS)/*.c\033[0m"
	@norminette $(DIR_MS)/*.c
	@echo "\033[0;32mnorminette includes/*.h\033[0m"
	@norminette includes/*.h
	@echo "\033[0;32mnorminette $(LIBFT)/*.c\033[0m"
	@norminette $(LIBFT)/*.{c,h}
clean:
	@echo "\033[0;33m"
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)

fclean: clean
	@echo "\033[0;33m"
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all lib clean fclean re

-include $(OBJS:.o=.d)
-include $(B_OBJS:.o=.d)