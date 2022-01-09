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
	tet->prev = -1;
	return (tet);
}

int	handle_gnl_ret(size_t ret, t_tet **tet, char **line)
{
	if (ret == 0)
	{
		ft_strdel(line);
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
		if (handle_gnl_ret(ret, &(tets[i]), &line))
			break ;
		validate_line(line, line_no, tets[i]);
		ft_strdel(&line);
		line_no++;
	}
	if (line_no % 5 != 0 || line)
		invalid_input("file should end with empty line");
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
	int		leftmost;
	int		rightmost;

	i = 0;
	while (tets[i])
	{
		j = 0;
		tets[i]->width = 1;
		tets[i]->height = 1;
		leftmost = 0;
		rightmost = 0;
		while (j < 7)
		{
			if ((size_t) tets[i]->coords[j] + 1> tets[i]->height)
				tets[i]->height = tets[i]->coords[j] + 1;
			if (tets[i]->coords[j + 1] < (-1 * (int) tets[i]->left_offset))
				tets[i]->left_offset = (size_t)(-1 * tets[i]->coords[j + 1]);
			if (tets[i]->coords[j + 1] < leftmost)
				leftmost = tets[i]->coords[j + 1];
			if (tets[i]->coords[j + 1] > rightmost)
				rightmost = tets[i]->coords[j + 1];
			j += 2;
		}
		tets[i]->width = (size_t)(rightmost - leftmost + 1);
		i++;
	}
}

void	ft_arraypush(void **array, void *el)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	array[i] = el;
}

int	shape_in_array(t_shape **shapes, int *coords)
{
	size_t	i;

	i = 0;
	while (shapes[i])
	{
		if (ft_memcmp(shapes[i]->coords, coords, 32) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_shapes(t_tet **tets, t_shape **shapes)
{
	size_t	i;
	t_shape	*shape;

	i = 0;
	while (tets[i])
	{
		if (shape_in_array(shapes, tets[i]->coords))
		{
			tets[i]->prev = shape->index;
			shape->index = i;
		}
		else
		{
			shape = (t_shape *)malloc(sizeof(t_shape));
			if (!shape) // handle error
				return (0);
			ft_memcpy(shape->coords, tets[i]->coords, 32);
			shape->index = i;
			ft_arraypush((void **)shapes, shape);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_tet	*tets[27];
	t_shape	*shapes[30];

	ft_bzero(shapes, sizeof(t_shape *) * 30);
	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	ft_bzero(tets, sizeof(t_tet *) * 27);
	get_tetriminos(argv[1], tets);
	get_dimensions(tets);
	get_shapes(tets, shapes);
	solve(tets);
	free_tetriminos(tets);
	return (0);
}
