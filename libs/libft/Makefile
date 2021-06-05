# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 19:56:48 by dbaron            #+#    #+#              #
#    Updated: 2020/11/10 21:28:31 by dbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_isalpha.c\
			ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c ft_toupper.c\
			ft_tolower.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strlcat.c\
			ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
			ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS		= $(addprefix , ${SRCS:.c=.o})

BONUS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS	= $(addprefix , ${BONUS:.c=.o})

HEADER = libft.h

NAME		= libft.a

%.o:		%.c $(HEADER)
			gcc -Wall -Wextra -Werror -c -I.$(HEADER) $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
			ar rc $@ $^

all:		$(NAME)

clean:
			rm -f $(OBJS) $(BONUS_OBJS)

fclean:		clean
			rm -f $(NAME) $(BONUS_OBJS)

bonus:		$(BONUS_OBJS)
			ar rc $(NAME) $^

re:			fclean all
