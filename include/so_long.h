/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:25:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/11 14:23:55 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

//Allowed functions
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "../libft/libft.h"
//# include "../minilibx/mlx.h"
# include <mlx.h>

char	*concat_str(char *memory, char *buf);
char	**check_map(char *map);
void	free_dp(char **line);

typedef struct s_check
{
	int	e;
	int	p;
	int	c;
}	t_check;

#endif
