# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 22:19:13 by gartaud           #+#    #+#              #
#    Updated: 2021/06/11 12:26:02 by gartaud          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		= philo
DEPS_DIR	= .
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3 -I ./$(DEPS_DIR)
LFLAGS		= -lpthread
DEPS		= philo.h
FILES		= $(shell find src *.c -type f 2> /dev/null)
OBJ 		= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norme:
	norminette $(FILES) $(DEPS)

.PHONY: clean fclean all re
