/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:54:33 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 19:48:14 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"
#include "fcntl.h"
#include "get_next_line.h"

t_tet	*new_tetrimino(size_t i)
{
	t_tet	*tet;

	tet = (t_tet *) malloc(sizeof (t_tet));
	if (!tet)
		return (NULL);
	tet->symbol = 'A' + i;
	return (tet);
}

int	handle_gnl_ret(size_t ret, t_tet **tet)
{
	if (ret == 0)
	{
		ft_memdel((void *) tet);
		return (1);
	}
	if (ret < 0)
		exit(1);
	return (0);
}

void	get_tetriminos(char *filename, t_tet **tets)
{
	int		fd;
	int		ret;
	size_t	i;
	size_t	line_no;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	line_no = 1;
	i = 0;
	tets[0] = new_tetrimino(0);
	while (1)
	{
		if (line_no % 5 == 0)
		{
			validate_tetrimino(tets[i++]);
			tets[i] = new_tetrimino(i);
		}
		ret = get_next_line(fd, &line);
		if (handle_gnl_ret(ret, &(tets[i])))
			break ;
		validate_line(line, line_no, tets[i]);
		line_no++;
	}
}

void	free_tetriminos(t_tet **tets)
{
	size_t	i;

	i = 0;
	while (tets[i])
		free(tets[i++]);
}

void	get_dimensions(t_tet **tets)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tets[i])
	{
		j = 0;
		tets[i]->width = 1;
		tets[i]->height = 1;
		while (j < 7)
		{
			if ((size_t) tets[i]->coords[j] + 1> tets[i]->height)
				tets[i]->height = tets[i]->coords[j] + 1;
			if ((size_t) tets[i]->coords[j + 1] + 1 > tets[i]->width)
				tets[i]->width = tets[i]->coords[j + 1] + 1;
			j += 2;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_tet	*tets[27];

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	ft_bzero(tets, sizeof(t_tet *) * 27);
	get_tetriminos(argv[1], tets);
	get_dimensions(tets);
	solve(tets);
	free_tetriminos(tets);
	return (0);
}
