/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:48:28 by mde-maul          #+#    #+#             */
/*   Updated: 2022/01/17 13:48:31 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	handle_error(t_tet **tets)
{
	free_tetriminos(tets);
	ft_putstr("error\n");
	exit(1);
}
