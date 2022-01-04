#include <stdio.h>
#include <stdlib.h>
#include "fillit.h"
#include "fcntl.h"
#include "get_next_line.h"

void	invalid_input(char *err)
{
	printf("%s ", err);
	ft_putstr("error\n");
	// It might be necessary to free some stuff here
	exit(1);
}

void	validate_line(char *line, size_t line_no, t_tetrimino *tetrimino)
{	
	static int		prev[2];
	static int		block_count;
	int				j;
 
	if (line_no % 5 == 0 && *line != '\0')
		invalid_input("not empty line between tetriminos");
	else if (line_no % 5 == 0)
		block_count = 0;
	else
	{
		j = 0;
		while (line[j])
		{
			if (j > 3)
				invalid_input("too long line");
			if (line[j] != '.' && line[j] != '#')
				invalid_input("invalid character");
			if (line[j] == '#')
			{
				block_count++;
				if (block_count > 4)
					invalid_input("too many blocks");
				if (block_count == 2)
				{
					tetrimino->coords[0] = (line_no % 5) - 1 - prev[0];
					tetrimino->coords[1] = j - prev[1];
				}
				if (block_count == 3)
				{
					tetrimino->coords[2] = (line_no % 5) - 1 - prev[0];
					tetrimino->coords[3] = j - prev[1];
				}
				if (block_count == 4)
				{
					tetrimino->coords[4] = (line_no % 5) - 1 - prev[0];
					tetrimino->coords[5] = j - prev[1];
				}
				prev[1] = j;
				prev[0] =  (int) (line_no % 5) - 1;
			}
			j++;
		}
		if (j != 4)
			invalid_input("too short line");
	}
}

t_tetrimino	*new_tetrimino(void)
{
	t_tetrimino	*tetrimino;

	tetrimino = (t_tetrimino *) malloc(sizeof (t_tetrimino));
	if (!tetrimino)
		return (NULL);
	return (tetrimino);
}

void	validate_tetrimino(t_tetrimino *tetrimino)
{
	size_t	i;
	int		row;
	int		col;
	int		prevrow;
	int		prevcol;

	i = 0;
	prevrow = 0;
	prevcol = 0;
	while (i < 6)
	{
		row = tetrimino->coords[i];
		col = tetrimino->coords[i+1];
		printf("row: %d, col: %d\tprevrow: %d, prevcol: %d\n", row, col, prevrow, prevcol);
		if (row + ft_abs(col) != 1)
			printf("gap between blocks\n");
		i += 2;
	}
}

void	get_tetriminos(char *filename, t_tetrimino **tetriminos)
{
	int			fd;
	int			ret;
	size_t		i;
	size_t		line_no;
	char		*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	line_no = 1;
	i = 0;
	tetriminos[0] = new_tetrimino();
	while (1)
	{
		if (line_no % 5 == 0) // Empty line between tetriminos
		{
			validate_tetrimino(tetriminos[i]);
			i++;
			tetriminos[i] = new_tetrimino();
		}
		ret = get_next_line(fd, &line);
		if (ret == 0)
			break ;
		if (ret < 0)
			exit(1);
		validate_line(line, line_no, tetriminos[i]);
		line_no++;
	} 
}

void	free_tetriminos(t_tetrimino **tetriminos)
{
	size_t	i;

	i = 0;
	while (tetriminos[i])
		free(tetriminos[i++]);
}

void	print_tetriminos(t_tetrimino **tetriminos)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tetriminos[i])
	{
		j = 0;
		while (j < 6)
		{
			printf("%d, ", tetriminos[i]->coords[j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

int		main(int argc, char **argv)
{
	t_tetrimino	*tetriminos[26];

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	ft_bzero(tetriminos, sizeof(t_tetrimino	*) * 26);
	get_tetriminos(argv[1], tetriminos);
	print_tetriminos(tetriminos);
	free_tetriminos(tetriminos);
	return (0);
}
