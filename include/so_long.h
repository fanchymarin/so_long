/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:25:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/15 19:59:39 by fmarin-p         ###   ########.fr       */
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

//Additional libraries
# include "../libft/libft.h"
# include <mlx.h>

#define PSIZE 32

typedef struct s_map
{
	int	e;
	int	p;
	int	c;
	int	height;
	int	width;

}	t_map;

struct s_images
{
	void	*f1;
	void	*f2;
	void	*f3;
	void	*r1;
	void	*r2;
	void	*r3;
	void	*downleft_c;
	void	*downright_c;
	void	*upleft_c;
	void	*upright_c;
	void	*down_w;
	void	*left_w;
	void	*right_w;
	void	*up_w;
};

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	struct s_images	images;
}	t_mlx;

char	*concat_str(char *memory, char *buf);
t_map	check_map(char *map, char **line);
void	free_dp(char **line);
void	map_error_handling(int error);
void	mlx_use(char **line, t_map stats);
void	error_handling(int error);

#endif
