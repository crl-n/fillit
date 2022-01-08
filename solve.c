/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:15:32 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 19:45:46 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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

	j = 2;
	grid->grid[k][l] = tet->symbol;
	while (j < 7)
	{
		row = k + tet->coords[j]; // ! Row and col can be negative, which could crash our program !
		col = l + tet->coords[j + 1];
		if (row >= grid->grid_size || col >= grid->grid_size
			|| grid->grid[row][col] != '.')
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
	return (1);
}

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

void	try_solution(t_grid *grid, t_tet **tets, size_t i)
{
	size_t	k;
	size_t	l;

	check_if_solved(tets[i], tets, grid);
	k = 0;
	while (k + tets[i]->height - 1 < grid->grid_size)
	{
		l = 0;
		while (l + tets[i]->width - 1 < grid->grid_size)
		{
			if (grid->grid[k][l] == '.')
			{
				if (tetrimino_fits(tets[i], grid, k, l))
				{
					try_solution(grid, tets, i + 1);
					remove_tetrimino(tets[i], grid, k, l);
					
				}
			}
			l++;
		}
		k++;
	}
}

/*
 * solve() calls try_solution.
 */

void	solve(t_tet **tets)
{
	t_grid	grid;
	size_t	i;
	size_t	min_area;

	i = 0;
	while (i < 32)
	{
		ft_memset((void *)grid.grid[i], '.', 31);
		grid.grid[i][31] = '\0';
		i++;
	}
	i = 0;
	min_area = 0;
	while (tets[i])
	{
		i++;
		min_area += 4;
	}
	grid.grid_size = ft_sqrt(min_area);;
	while (!ft_sqrt(min_area))
	{
		grid.grid_size = ft_sqrt(min_area - 4) + 1;
		min_area -= 4;
	}
	printf("grid_size at start: %zu\n", grid.grid_size);
	while (1)
	{
		try_solution(&grid, tets, 0);
		grid.grid_size++;
	}
}
