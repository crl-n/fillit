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

#include <stdlib.h>
#include "fillit.h"
#include "fcntl.h"
#include "get_next_line.h"

t_tetrimino	*new_tetrimino(size_t i)
{
	t_tetrimino	*tetrimino;

	tetrimino = (t_tetrimino *) malloc(sizeof (t_tetrimino));
	if (!tetrimino)
		return (NULL);
	tetrimino->symbol = 'A' + i;
	return (tetrimino);
}

int	handle_gnl_ret(size_t ret, t_tetrimino **tetrimino)
{
	if (ret == 0)
	{
		ft_memdel((void *) tetrimino);
		return (1);
	}
	if (ret < 0)
		exit(1);
	return (0);
}

void	get_tetriminos(char *filename, t_tetrimino **tetriminos)
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
	tetriminos[0] = new_tetrimino(0);
	while (1)
	{
		if (line_no % 5 == 0)
		{
			validate_tetrimino(tetriminos[i++]);
			tetriminos[i] = new_tetrimino(i);
		}
		ret = get_next_line(fd, &line);
		if (handle_gnl_ret(ret, &(tetriminos[i])))
			break ;
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

int	main(int argc, char **argv)
{
	t_tetrimino	*tetriminos[27];

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	ft_bzero(tetriminos, sizeof(t_tetrimino *) * 27);
	get_tetriminos(argv[1], tetriminos);
	print_tetriminos(tetriminos);
	solve(tetriminos);
	free_tetriminos(tetriminos);
	return (0);
}
