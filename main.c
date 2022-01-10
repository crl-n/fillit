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

t_tet	*new_tetrimino(size_t i)
{
	t_tet	*tet;

	tet = (t_tet *) malloc(sizeof (t_tet));
	if (!tet)
		return (NULL);
	tet->symbol = 'A' + i;
	tet->prev = NULL;
	tet->grid_placement[0] = 0;
	tet->grid_placement[1] = 0;
	tet->height = 1;
	tet->width = 1;
	tet->left_offset = 0;
	return (tet);
}

void	free_tetriminos(t_tet **tets)
{
	size_t	i;

	i = 0;
	while (tets[i])
		free(tets[i++]);
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
	handle_file(argv[1], tets);
	get_dimensions(tets);
	get_prevs(tets);
	solve(tets);
	free_tetriminos(tets);
	return (0);
}
