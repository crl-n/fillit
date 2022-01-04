#include <stdio.h>
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

void	validate_line(char *line, size_t line_no)
{	
	static int	prev[2];
	int			j;
 
	if (line_no % 5 == 0 && *line != '\0')
		invalid_input("not empty line between tetriminos");
	else if (line_no % 5 == 0)
		return ;
	else
	{
		prev[0] =  (int) (line_no % 5) - 1;
		j = 0;
		while (line[j])
		{
			if (j > 3)
				invalid_input("too long line");
			if (line[j] != '.' && line[j] != '#')
				invalid_input("invalid character");
			if (line[j] == '#')
				prev[1] = j;
			j++;
		}
		if (j != 4)
			invalid_input("too short line");
	}
}

void	get_tetriminos(char *filename, t_tetrimino **tetriminos)
{
	int			fd;
	int			ret;
	size_t		line_no;
	char		*line;

	(void) tetriminos;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	line_no = 1;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			break ;
		if (ret < 0)
			exit(1);
		validate_line(line, line_no);
		line_no++;
	}
}

int	main(int argc, char **argv)
{
	t_tetrimino	*tetriminos[26];

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	get_tetriminos(argv[1], tetriminos);
	return (0);
}
