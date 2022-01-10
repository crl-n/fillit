/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:00:31 by mde-maul          #+#    #+#             */
/*   Updated: 2022/01/10 19:00:33 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "fcntl.h"
#include "get_next_line.h"

int	handle_gnl_ret(size_t ret, t_tet **tet, char **line)
{
	if (ret == 0)
	{
		ft_memdel((void *) tet);
		return (1);
	}
	if (ret < 0)
	{
		ft_strdel(line);
		exit(1);
	}
	return (0);
}

void	get_tetriminos(int fd, t_tet **tets)
{
	size_t	i;
	int		ret;
	char	*line;
	size_t	line_no;

	i = 0;
	line = NULL;
	line_no = 1;
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

void	handle_file(char *filename, t_tet **tets)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		invalid_input("error");
	get_tetriminos(fd, tets);
}
