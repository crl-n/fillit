/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:54:33 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/05 15:07:16 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fillit.h"
#include "fcntl.h"
#include "get_next_line.h"

void	invalid_input(char *err)
{
	printf("%s ", err);
	ft_putstr("error\n");
	// It might be necessary to free some stuff here
	exit(1);
}

void	validate_line(char *line, size_t line_no, t_tetrimino *tetrimino)
{	
	static int		first_coord[2];
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
			{
				block_count++;
				if (block_count > 4)
					invalid_input("too many blocks");
				if (block_count == 1)
				{
					tetrimino->coords[0] = 0;
					tetrimino->coords[1] = 0;
					first_coord[0] =  (int) (line_no % 5) - 1;
					first_coord[1] = j;
				}
				if (block_count > 1)
				{
					tetrimino->coords[(block_count - 2) * 2 + 2] = (line_no % 5) - 1 - first_coord[0];
					tetrimino->coords[(block_count - 2) * 2 + 2 + 1] = j - first_coord[1];
				}
			}
			j++;
		}
		if (j != 4)
			invalid_input("too short line");
	}
}

t_tetrimino	*new_tetrimino(void)
{
	t_tetrimino	*tetrimino;

	tetrimino = (t_tetrimino *) malloc(sizeof (t_tetrimino));
	if (!tetrimino)
		return (NULL);
	return (tetrimino);
}

/*
 * The function validate_tetrimino() checks if all blocks in a tetrimino are connected to each other.
 *
 * The int array dists contains the Manhattan distances of each tetrimino block to each other.
 */

void	validate_tetrimino(t_tetrimino *tetrimino)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		dists[6];
	size_t	ones;

	i = 0;
	k = 0;
	while (i < 7)
	{
		j = i + 2;
		while (j < 7)
		{
			dists[k++] = (tetrimino->coords[j] - tetrimino->coords[i]) + (tetrimino->coords[j + 1] - tetrimino->coords[i + 1]);
			j += 2;
		}
		i += 2;
	}
	i = 0;
	ones = 0;
	while (i < 6)
	{
		if (dists[i] == 1)
			ones++;
		i++;
	}
	if (ones < 3)
		invalid_input("all tetrimino blocks are not connected");
}

void	get_tetriminos(char *filename, t_tetrimino **tetriminos)
{
	int			fd;
	int			ret;
	size_t		i;
	size_t		line_no;
	char		*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	line_no = 1;
	i = 0;
	tetriminos[0] = new_tetrimino();
	while (1)
	{
		if (line_no % 5 == 0) // Empty line between tetriminos
		{
			validate_tetrimino(tetriminos[i]);
			i++;
			tetriminos[i] = new_tetrimino();
		}
		ret = get_next_line(fd, &line);
		if (ret == 0)
		{
			ft_memdel((void *) &(tetriminos[i]));
			break ;
		}
		if (ret < 0)
			exit(1);
		validate_line(line, line_no, tetriminos[i]);
		line_no++;
	} 
}

void	free_tetriminos(t_tetrimino **tetriminos)
{
	size_t	i;

	i = 0;
	while (tetriminos[i])
		free(tetriminos[i++]);
}

void	print_tetriminos(t_tetrimino **tetriminos)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tetriminos[i])
	{
		j = 0;
		while (j < 8)
		{
			printf("%d, ", tetriminos[i]->coords[j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

int		main(int argc, char **argv)
{
	t_tetrimino	*tetriminos[26];

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	ft_bzero(tetriminos, sizeof(t_tetrimino	*) * 26);
	get_tetriminos(argv[1], tetriminos);
	print_tetriminos(tetriminos);
	free_tetriminos(tetriminos);
	return (0);
}
