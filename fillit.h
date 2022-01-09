/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:08:49 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 19:48:34 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdio.h> // DELETE

typedef struct s_tet
{
	char	symbol;
	int		coords[8];
	size_t	width;
	size_t	height;
	size_t	prev;
	size_t	grid_placement[2];
} t_tet;

typedef struct s_grid
{
	size_t	grid_size;
	char	grid[32][32];
} t_grid;

typedef struct s_shape
{
	int		coords[8];
	size_t	index;
} t_shape;

# define USAGE "usage: ./fillit input_file\n"

void	validate_tetrimino(t_tet *tet);
void	validate_line(char *line, size_t line_no, t_tet *tet);
void	free_tetriminos(t_tet **tets);
void	solve(t_tet **tets);
void	display_solution(t_grid *grid);
int	ft_sqrt(int nb);

// debugging functions. DELETE
void	print_tetrimino(t_tet *tet);
void	print_tetriminos(t_tet **tets);
void	display_grid(t_grid *grid);
void	display_solution_prettier(t_grid *grid);
void	print_shapes(t_shape **shapes);

#endif
