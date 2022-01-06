#include "fillit.h"
#include <stdio.h>

void	print_tetrimino(t_tetrimino *tetrimino)
{
	int 	j;

	j = 0;
	while (j < 8)
	{
		printf("%d, ", tetrimino->coords[j]);
		j++;
	}
	printf("\n");
}

void	print_tetriminos(t_tetrimino **tetriminos)
{
	size_t	i;

	i = 0;
	printf("all the tetriminos:\n");
	while (tetriminos[i])
	{
		print_tetrimino(tetriminos[i]);
		i++;
	}
}

void    display_grid(t_grid *grid)
{
    size_t i;

    i = 0;
    printf("\ngrid size is: %zu\n", grid->grid_size);
    while (i < grid->grid_size)
    {
        write(1, grid->grid[i], grid->grid_size);
        ft_putchar('\n');
        i++;
    }
}

void	display_solution_prettier(t_grid *grid)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < grid->grid_size)
	{
        j = 0;
        while (j < grid->grid_size)
        {
            ft_putchar(grid->grid[i][j]);
            write(1, " ", 1);
            j++;
        }
        write(1, "\n", 1);
		i++;
	}
}
