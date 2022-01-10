NAME = fillit

SRCS = main.c \
	   get_next_line.c \
	   validate_input.c \
	   solve.c \
	   tetrimino_fits.c \
	   try_solution.c \
	   display_solution.c \
	   debugging_functions.c \
	   handle_tetriminos.c \
	   handle_file.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -Wall -Werror -Wextra -g -c $(SRCS)
	gcc -Wall -Werror -Wextra -g -o $(NAME) $(OBJS) -L./libft -lft

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
