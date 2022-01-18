/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:27:38 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 19:50:19 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

/*
 * The function fill_dists() gets the Manhattan distances used in
 * validate_tetrimino().
 */

void	fill_dists(t_tet *tet, int *dists)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (i < 7)
	{
		j = i + 2;
		while (j < 7)
		{
			dists[k++] = (tet->coords[j] - tet->coords[i]) + \
				ft_abs((tet->coords[j + 1] - tet->coords[i + 1]));
			j += 2;
		}
		i += 2;
	}
}

/*
 * The function validate_tetrimino() checks if all blocks in a tetrimino
 * are connected to each other.
 *
 * The int array dists contains the Manhattan distances of each tetrimino
 * block to each other. A valid tetrimino will have either 3 or 4 distances
 * of 1. If it has less, there is at least one gap between blocks.
 */

void	validate_tetrimino(t_tet *tet, t_tet **tets)
{
	size_t	ones;
	size_t	i;
	int		dists[6];

	i = 0;
	ones = 0;
	fill_dists(tet, dists);
	while (i < 6)
	{
		if (dists[i] == 1)
			ones++;
		i++;
	}
	if (ones < 3)
		handle_error(tets);
}

void	handle_block(size_t *block_count, t_tet *tet, int j, t_tet **tets)
{
	static int		first_coord[2];

	(*block_count)++;
	if (*block_count > 4)
		handle_error(tets);
	if (*block_count == 1)
	{
		tet->coords[0] = 0;
		tet->coords[1] = 0;
		first_coord[0] = (int)j / 5;
		first_coord[1] = j % 5;
	}
	if (*block_count > 1)
	{
		tet->coords[(*block_count - 2) * 2 + 2] = (int)j / 5 - first_coord[0];
		tet->coords[(*block_count - 2) * 2 + 2 + 1] = j % 5 - first_coord[1];
	}
}

/*
 * The function validate_tet_map() checks if:
 * 		∙ Lines between tetriminos are empty
 * 		∙ Each line consists of valid characters
 * 		∙ Lines are of correct length
 *
 * validate_line() also calls handle_block() when a block is found.
 */

void	validate_tet_map(char *buff, ssize_t i, t_tet *tet, t_tet **tets)
{
	ssize_t			j;
	static size_t	block_count;

	j = 0;
	block_count = 0;
	if (buff[i + 4] != '\n' || buff[i + 9] != '\n' || buff[i + 14] != '\n' \
		|| buff[i + 19] != '\n' || buff[i + 20] != '\n')
		handle_error(tets);
	while (j < 21)
	{
		if (j == 4 || j == 9 || j == 14 || j == 19 || j == 20)
		{
			j++;
			continue ;
		}
		if (buff[j + i] != '#' && buff[j + i] != '.')
			handle_error(tets);
		if (buff[j + i] == '#')
			handle_block(&block_count, tet, j, tets);
		j++;
	}
	validate_tetrimino(tet, tets);
}
