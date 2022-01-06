#include <stdio.h>

int	main(void)
{
	char	str[4][5] = {"####", ".#..", "..#.", "...#"};
	int		nb = 0b1000000000000000;
	int		ret = 0;
	size_t	i = 0;
	size_t	j = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (str[i][j] == '#')
				ret = ret | nb;
			nb = nb >> 1;
			j++;
		}
		i++;
	}
	printf("hex: %x, dec: %d\n", ret, ret);
	return (0);
}
