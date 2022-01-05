/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:08:49 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/05 14:08:56 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdio.h> // DELETE

typedef struct s_tetrimino
{
	int	coords[6];
} t_tetrimino;

# define USAGE "usage: ./fillit input_file\n"

void	validate_tetrimino(t_tetrimino *tetrimino);
void	validate_line(char *line, size_t line_no, t_tetrimino *tetrimino);

#endif
