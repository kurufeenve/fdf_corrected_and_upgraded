# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 19:33:22 by vordynsk          #+#    #+#              #
#    Updated: 2018/02/13 19:33:24 by vordynsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEADER = fdf.h

SOURCES = main.c line.c init.c map.c other_stuff.c

OBJFILES = main.o line.o init.o map.o other_stuff.o

MAKE = make

FLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	@echo "\033[0;33mcompiling libft...\033[0m"
	@$(MAKE) -C libft/
	@echo "\033[0;32mcompleted\n\033[0;33mcompiling FDF...\033[0m"
	@gcc $(FLAGS) -o $(NAME) $(SOURCES) -I $(HEADER) libft/libft.a
	@echo "\033[0;32mcompleted\033[0m"

clean:
	@$(MAKE) clean -C libft/
	@rm -f $(OBJFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
