/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:08:49 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 14:43:19 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdio.h> // DELETE

typedef struct s_tetrimino
{
	char	symbol;
	int		coords[8];
} t_tetrimino;

typedef struct s_grid
{
	size_t	grid_size;
	char	grid[16][16];
} t_grid;

# define USAGE "usage: ./fillit input_file\n"

void	validate_tetrimino(t_tetrimino *tetrimino);
void	validate_line(char *line, size_t line_no, t_tetrimino *tetrimino);
void	free_tetriminos(t_tetrimino **tetriminos);
void	solve(t_tetrimino **tetriminos);
void	display_solution(t_grid *grid)

// debugging functions. DELETE
void	print_tetrimino(t_tetrimino *tetrimino);
void	print_tetriminos(t_tetrimino **tetriminos);
void    display_grid(t_grid *grid);
void	display_solution_prettier(t_grid *grid);

#endif
