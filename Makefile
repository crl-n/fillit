NAME = fillit

SRCS = main.c \
	   get_next_line.c \
	   validate_input.c \
	   solve.c \
	   display_solution.c \
	   debugging_functions.c \
<<<<<<< Updated upstream
	   ft_sqrt.c \
	   handle_tetriminos.c \
	   handle_file.c
=======
<<<<<<< HEAD
	   tetrimino_fits.c \
	   try_solution.c \
=======
	   ft_sqrt.c \
	   handle_tetriminos.c \
	   handle_file.c
>>>>>>> 1c8ef2aa23fd93e055610e20159dc5f6ac1a2e81
>>>>>>> Stashed changes

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -g -c $(SRCS)
	gcc -Wall -Werror -Wextra -g -o $(NAME) $(OBJS) -L./libft -lft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
