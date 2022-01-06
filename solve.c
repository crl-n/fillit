/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:15:32 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/05 16:16:25 by cnysten          ###   ########.fr       */
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

int		tetrimino_fits(t_tetrimino *tetrimino, t_grid *grid, size_t k, size_t l)
{
	size_t	j;
	size_t	row;
	size_t	col;

	j = 0;
	while (j < 7)
	{
		row = k + tetrimino->coords[j];
		col = l + tetrimino->coords[j + 1];
		if (row >= grid->grid_size || col >= grid->grid_size || grid->grid[row][col] != '.')
		{
			while (j > 0)
			{
				j -= 2;
				row = k + tetrimino->coords[j];
				col = l + tetrimino->coords[j + 1];
				grid->grid[row][col] = '.';
			}
			grid->grid[k][l] = '.';
			return (0);
		}
		grid->grid[row][col] = tetrimino->symbol;
		j += 2;
	}
	return (1);
}

void	remove_tetrimino(t_tetrimino *tetrimino, t_grid *grid, size_t k, size_t l)
{
	size_t	j;
	size_t	row;
	size_t	col;

	j = 0;
	while (j < 7)
	{
		row = k + tetrimino->coords[j];
		col = l + tetrimino->coords[j + 1];
		grid->grid[row][col] = '.';
		j += 2;
	}
}

void	display_solution(t_grid *grid)
{
	size_t	i;

	i = 0;
	while (i < grid->grid_size)
	{
		write(1, grid->grid[i], grid->grid_size);
		write(1, "\n", 1);
		i++;
	}
}

void	check_if_solved(t_tetrimino *tetrimino, t_tetrimino **tetriminos, t_grid *grid)
{
	if (!tetrimino)
	{
		display_solution(grid);
		free_tetriminos(tetriminos);
		exit(0);
	}
}

void	try_solution(t_grid *grid, t_tetrimino **tetriminos, size_t i)
{
	size_t	k;
	size_t	l;
	
	check_if_solved(tetriminos[i], tetriminos, grid);
	k = 0;
	while (k < grid->grid_size)
	{
		l = 0;
		while (l < grid->grid_size)
		{
			if (grid->grid[k][l] == '.')
			{
				if (tetrimino_fits(tetriminos[i], grid, k, l))
				{
					try_solution(grid, tetriminos, i + 1);
					remove_tetrimino(tetriminos[i], grid, k, l);
				}
			}
			l++;
		}
		k++;
	}
}

void	solve(t_tetrimino **tetriminos)
{
	t_grid	grid;
	size_t i;

	i = 0;
	while (i < 16)
	{
		ft_memset((void *)grid.grid[i], '.', 16);
		i++;
	}
	grid.grid_size = 2;
	while (1)
	{
		try_solution(&grid, tetriminos, 0);
		grid.grid_size++;
	}
}
