NAME = fillit

SRCS = main.c \
	   get_next_line.c \
	   validate_input.c \
	   solve.c \
	   display_solution.c \
	   debugging_functions.c \
	   ft_sqrt.c

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
