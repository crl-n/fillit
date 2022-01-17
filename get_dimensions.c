/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tetriminos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:57:38 by mde-maul          #+#    #+#             */
/*   Updated: 2022/01/10 18:57:42 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	calc_dimensions(t_tet **tets, size_t i)
{
	size_t	j;
	int		leftmost;
	int		rightmost;

	j = 0;
	leftmost = 0;
	rightmost = 0;
	while (j < 7)
	{
		if ((size_t) tets[i]->coords[j] + 1 > tets[i]->height)
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
}

void	get_dimensions(t_tet **tets)
{
	size_t	i;

	i = 0;
	while (tets[i])
	{
		tets[i]->width = 1;
		tets[i]->height = 1;
		calc_dimensions(tets, i);
		i++;
	}
}
