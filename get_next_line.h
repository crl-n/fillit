/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:27:25 by mde-maul          #+#    #+#             */
/*   Updated: 2021/12/02 13:27:27 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"

# define BUFF_SIZE 200
# define FD_ARRAY_SIZE 4096

int	get_next_line(const int fd, char **line);

#endif
