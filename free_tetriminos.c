/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tetriminos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:58:29 by mde-maul          #+#    #+#             */
/*   Updated: 2022/01/17 13:58:31 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

void	free_tetriminos(t_tet **tets)
{
	size_t	i;

	i = 0;
	while (tets[i])
		free(tets[i++]);
}
