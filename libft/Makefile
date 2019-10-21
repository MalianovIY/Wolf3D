# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmicha <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 16:44:45 by cmicha            #+#    #+#              #
#    Updated: 2019/04/05 17:13:14 by cmicha           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

all: $(NAME)

OBJ = $(patsubst %.c,%.o,$(wildcard *.c))

$(NAME): $(OBJ)
	ar rc $(NAME) $^
	ranlib $(NAME)

%.o: %.c
	gcc -Wall -Werror -Wextra -c $^ -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf libft.a

re: fclean all

.PHONY: all clean fclean re
