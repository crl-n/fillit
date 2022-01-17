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
#include <unistd.h>

t_tet	*new_tetrimino(size_t i, t_tet **tets)
{
	t_tet	*tet;

	tet = (t_tet *) malloc(sizeof (t_tet));
	if (!tet)
		handle_error(tets);
	tet->symbol = 'A' + i;
	tet->prev = NULL;
	tet->grid_placement[0] = 0;
	tet->grid_placement[1] = 0;
	tet->height = 1;
	tet->width = 1;
	tet->left_offset = 0;
	return (tet);
}

void	get_tetriminos(int fd, t_tet **tets)
{
	ssize_t		i;
	ssize_t		ret;
	char		buff[547];

	ret = read(fd, buff, 546);
	if (ret <= 0 || ret == 546 || ((ret + 1) % 21 != 0))
		handle_error(tets);
	if (buff[ret - 1] == '\n' && buff[ret - 2] == '\n')
		handle_error(tets);
	buff[ret] = '\n';
	buff[ret + 1] = '\0';
	i = 0;
	while (i < ret)
	{
		tets[i / 21] = new_tetrimino(i / 21, tets);
		validate_tet_map(buff, i, tets[i / 21], tets);
		i += 21;
	}
}
