/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:08:49 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/10 21:01:13 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"

typedef struct s_tet
{
	char			symbol;
	int				coords[8];
	size_t			width;
	size_t			height;
	size_t			left_offset;
	struct s_tet	*prev;
	size_t			grid_placement[2];
}					t_tet;

typedef struct s_grid
{
	size_t	grid_size;
	char	grid[32][32];
}				t_grid;

# define USAGE "usage: ./fillit input_file\n"

void	validate_tetrimino(t_tet *tet);
void	validate_tet_map(char *buff, ssize_t i, t_tet *tet);
void	free_tetriminos(t_tet **tets);
void	solve(t_tet **tets);
void	display_solution(t_grid *grid);
int		ft_sqrt(int nb);
void	try_solution(t_grid *grid, size_t grid_size, t_tet **tets, size_t i);
int		tetrimino_fits(t_tet *tet, t_grid *grid, size_t k, size_t l);
void	invalid_input(void);
void	get_prevs(t_tet **tets);
void	get_dimensions(t_tet **tets);
void	handle_file(char *filename, t_tet **tets);
t_tet	*new_tetrimino(size_t i);

#endif
