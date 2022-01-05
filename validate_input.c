/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:27:38 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/05 16:04:46 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	invalid_input(char *err)
{
	printf("%s ", err);
	ft_putstr("error\n");
	// It might be necessary to free some stuff here
	exit(1);
}

void	handle_block(int block_count, t_tetrimino *tetrimino, size_t line_no,
	int j)
{
	static int		first_coord[2];

	block_count++;
	if (block_count > 4)
		invalid_input("too many blocks");
	if (block_count == 1)
	{
		tetrimino->coords[0] = 0;
		tetrimino->coords[1] = 0;
		first_coord[0] = (int)(line_no % 5) - 1;
		first_coord[1] = j;
	}
	if (block_count > 1)
	{
		tetrimino->coords[(block_count - 2) * 2 + 2] = (line_no % 5) - 1 - \
			first_coord[0];
		tetrimino->coords[(block_count - 2) * 2 + 2 + 1] = j - first_coord[1];
	}
}

/*
 * The function validate_line() checks if:
 * 		∙ Lines between tetriminos are empty
 * 		∙ Each line consists of valid characters
 * 		∙ Lines are of correct length
 *
 * validate_line() also calls handle_block() when a block is found.
 */

void	validate_line(char *line, size_t line_no, t_tetrimino *tetrimino)
{
	static int		block_count;
	int				j;

	if (line_no % 5 == 0)
	{
		block_count = 0;
		if (*line != '\0')
			invalid_input("not empty line between tetriminos");
	}
	else
	{
		j = 0;
		while (line[j])
		{
			if (j > 3)
				invalid_input("too long line");
			if (line[j] != '.' && line[j] != '#')
				invalid_input("invalid character");
			if (line[j] == '#')
				handle_block(block_count, tetrimino, line_no, j);
			j++;
		}
		if (j != 4)
			invalid_input("too short line");
	}
}

/*
 * The function get_dists() gets the Manhattan distances used in
 * validate_tetrimino().
 */

void	fill_dists(t_tetrimino *tetrimino, int *dists)
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
			dists[k++] = (tetrimino->coords[j] - tetrimino->coords[i]) + \
				(tetrimino->coords[j + 1] - tetrimino->coords[i + 1]);
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

void	validate_tetrimino(t_tetrimino *tetrimino)
{
	size_t	ones;
	size_t	i;
	int		*dists;

	i = 0;
	ones = 0;
	dists = (int *) malloc(sizeof (int) * 6);
	if (!dists)
		exit(1);
	fill_dists(tetrimino, dists);
	while (i < 6)
	{
		if (dists[i] == 1)
			ones++;
		i++;
	}
	ft_memdel((void *) &dists);
	if (ones < 3)
		invalid_input("all tetrimino blocks are not connected");
}
