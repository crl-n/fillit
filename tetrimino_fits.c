/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_fits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:29:15 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/10 19:29:50 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	update_grid_placement(t_tet *tet, size_t k, size_t l)
{
	tet->grid_placement[0] = k;
	tet->grid_placement[1] = l;
}

int	is_collision(size_t	row, size_t col, t_grid *grid)
{
	if (row >= grid->grid_size)
		return (1);
	if (col >= grid->grid_size)
		return (1);
	if (grid->grid[row][col] != '.')
		return (1);
	return (0);
}

/*
 * The function tetrimino_fits() checks if a tetrimino can be placed at (k, l)
 * in the grid. If the tetrimino collides with an already placed tetrimino or
 * if the grid size would have to be increased for the tetramino to fit 0 is
 * returned. If the tetramino fits 1 is returned.
 *
 * As the function fits the tetrimino to the grid, the tetrimino's symbol is
 * filled to the grid. If the fit fails, the symbols are changed back into dots.
 */

int	tetrimino_fits(t_tet *tet, t_grid *grid, size_t k, size_t l)
{
	size_t	j;
	size_t	row;
	size_t	col;

	j = 0;
	while (j < 7)
	{
		row = k + tet->coords[j];
		col = (size_t)((int) l + tet->coords[j + 1]);
		if (is_collision(row, col, grid))
		{
			while (j > 0)
			{
				j -= 2;
				row = k + tet->coords[j];
				col = l + tet->coords[j + 1];
				grid->grid[row][col] = '.';
			}
			return (0);
		}
		grid->grid[row][col] = tet->symbol;
		j += 2;
	}
	update_grid_placement(tet, k, l);
	return (1);
}
