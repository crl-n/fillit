/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_solution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:32:12 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/10 19:32:56 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * remove_tetrimino() resets the characters in the grid to '.'.
 */

void	remove_tetrimino(t_tet *tet, t_grid *grid, size_t k, size_t l)
{
	size_t	j;
	size_t	row;
	size_t	col;

	j = 0;
	while (j < 7)
	{
		row = k + tet->coords[j];
		col = l + tet->coords[j + 1];
		grid->grid[row][col] = '.';
		j += 2;
	}
}

/*
 * If tetrimino is NULL, all tetriminos have been placed onto the map.
 * This means the correct solution has been found. In that case, the correct
 * solution is displayed and heap allocated memory is freed.
 */

void	check_if_solved(t_tet *tet, t_tet **tets, t_grid *grid)
{
	if (!tet)
	{
		display_solution(grid);
		free_tetriminos(tets);
		exit(0);
	}
}

void	set_start(size_t *k, size_t *l, t_tet *tet)
{
	*k = 0;
	*l = 0 + tet->left_offset;
	if (tet->prev)
	{
		*k = tet->prev->grid_placement[0];
		*l = tet->prev->grid_placement[1];
	}
}

void	try_solution(t_grid *grid, size_t grid_size, t_tet **tets, size_t i)
{
	size_t	k;
	size_t	l;

	check_if_solved(tets[i], tets, grid);
	set_start(&k, &l, tets[i]);
	while (k + tets[i]->height - 1 < grid_size)
	{
		while (l + tets[i]->width - tets[i]->left_offset - 1 < grid_size)
		{
			if (grid->grid[k][l] == '.')
			{
				if (tetrimino_fits(tets[i], grid, k, l))
				{
					try_solution(grid, grid_size, tets, i + 1);
					remove_tetrimino(tets[i], grid, k, l);
				}
			}
			l++;
		}
		k++;
		l = 0 + tets[i]->left_offset;
	}
}
