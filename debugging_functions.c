/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:17:50 by mde-maul          #+#    #+#             */
/*   Updated: 2022/01/10 19:17:53 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_tetrimino(t_tet *tet)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		ft_putnbr(tet->coords[j]);
		if (!(j % 2))
			ft_putchar(' ');
		j++;
		if (!(j % 2) && j != 8)
			ft_putstr(", ");
	}
	ft_putchar('\n');
}

void	print_tetriminos(t_tet **tets)
{
	size_t	i;

	i = 0;
	ft_putstr("The tetriminos:\n\n");
	while (tets[i])
	{
		print_tetrimino(tets[i]);
		ft_putchar('\n');
		i++;
	}
}

void	display_grid(t_grid *grid)
{
	size_t	i;

	i = 0;
	ft_putstr("\ngrid size is: ");
	ft_putnbr((int)grid->grid_size);
	ft_putchar('\n');
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
