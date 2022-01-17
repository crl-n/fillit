/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:42:26 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 14:46:48 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <unistd.h>

/*
 * display_solution() is used to display the solution when the correct
 * solution has been found.
 */

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
