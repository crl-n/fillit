#include "fillit.h"

void	get_prevs(t_tet **tets)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (tets[i])
	{
		j = i - 1;
		while (j >= 0)
		{
			if (ft_memcmp(tets[j]->coords, tets[i]->coords, 32) == 0)
			{
				tets[i]->prev = tets[j];
				break ;
			}
			if (j == 0)
				break ;
			j--;
		}
		i++;
	}
}
