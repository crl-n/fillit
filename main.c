#include <stdio.h>
#include "fillit.h"
#include "fcntl.h"

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(1);
	

}
