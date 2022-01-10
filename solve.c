/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:15:32 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/10 19:32:35 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static size_t	get_grid_size(t_tet **tets)
{
	size_t	count;
	size_t	grid_size;

	count = 0;
	while (tets[count])
		count++;
	grid_size = 2;
	while (grid_size * grid_size < count * 4)
		grid_size++;
	return (grid_size);
}

/*
 * solve() calls try_solution.
 */

void	solve(t_tet **tets)
{
	t_grid	grid;
	size_t	i;

	i = 0;
	while (i < 32)
	{
		ft_memset((void *)grid.grid[i], '.', 31);
		grid.grid[i][31] = '\0';
		i++;
	}
	grid.grid_size = get_grid_size(tets);
	while (1)
	{
		try_solution(&grid, grid.grid_size, tets, 0);
		grid.grid_size++;
	}
}
