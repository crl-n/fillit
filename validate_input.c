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

void	invalid_input(void)
{
	ft_putstr("error\n");
	exit(1);
}

void	handle_block(size_t *block_count, t_tet *tet, int j)
{
	static int		first_coord[2];

	(*block_count)++;
	if (*block_count > 4)
		invalid_input();
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

void	validate_tet_map(char *buff, ssize_t i, t_tet *tet)
{
	ssize_t			j;
	static size_t	block_count;

	j = 0;
	block_count = 0;
	if (buff[i + 4] != '\n' || buff[i + 9] != '\n' || buff[i + 14] != '\n' \
		|| buff[i + 19] != '\n' || buff[i + 20] != '\n')
		invalid_input();
	while (j < 21)
	{
		if (j == 4 || j == 9 || j == 14 || j == 19 || j == 20)
		{
			j++;
			continue ;
		}
		if (buff[j + i] != '#' && buff[j + i] != '.')
			invalid_input();
		if (buff[j + i] == '#')
			handle_block(&block_count, tet, j);
		j++;
	}
	validate_tetrimino(tet);
}

/*
 * The function get_dists() gets the Manhattan distances used in
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

void	validate_tetrimino(t_tet *tet)
{
	size_t	ones;
	size_t	i;
	int		*dists;

	i = 0;
	ones = 0;
	dists = (int *) malloc(sizeof (int) * 6);
	if (!dists)
		exit(1);
	fill_dists(tet, dists);
	while (i < 6)
	{
		if (dists[i] == 1)
			ones++;
		i++;
	}
	ft_memdel((void *) &dists);
	if (ones < 3)
		invalid_input();
}
