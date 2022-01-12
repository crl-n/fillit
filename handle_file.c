/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:00:31 by mde-maul          #+#    #+#             */
/*   Updated: 2022/01/10 20:58:29 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "fcntl.h"

int	handle_gnl_ret(int ret, t_tet **tet, char **line)
{
	if (ret == 0)
	{
		ft_memdel((void *) tet);
		return (1);
	}
	if (ret < 0)
	{
		ft_strdel(line);
		invalid_input();
	}
	return (0);
}

void	get_tetriminos(int fd, t_tet **tets)
{
	ssize_t		i;
	ssize_t		ret;
	char		buff[547];

	ret = read(fd, buff, 546);
	if (ret <= 0 || ret == 546 || ((ret + 1) % 21 != 0))
		invalid_input();
	if (buff[ret - 1] == '\n' && buff[ret - 2] == '\n')
		invalid_input();
	buff[ret] = '\n';
	buff[ret + 1] = '\0';
	i = 0;
	while (i < ret)
	{
		tets[i / 21] = new_tetrimino(i / 21);
		validate_tet_map(buff, i, tets[i / 21]);
		i += 21;
	}
}

void	handle_file(char *filename, t_tet **tets)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		invalid_input();
	get_tetriminos(fd, tets);
	close(fd);
}
