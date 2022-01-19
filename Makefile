# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnysten <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 19:13:25 by cnysten           #+#    #+#              #
#    Updated: 2022/01/19 13:35:50 by cnysten          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRCS = main.c \
	   validate_input.c \
	   solve.c \
	   tetrimino_fits.c \
	   try_solution.c \
	   display_solution.c \
	   get_dimensions.c \
	   get_prevs.c \
	   get_tetriminos.c \
	   handle_error.c \
	   free_tetriminos.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -Wall -Werror -Wextra -c $(SRCS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(OBJS) -L./libft -lft

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
