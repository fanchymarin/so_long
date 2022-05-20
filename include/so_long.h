/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:25:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/20 18:49:58 by fmarin-p         ###   ########.fr       */
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

# define PSIZE 64

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
	void	*dl_c;
	void	*dr_c;
	void	*ul_c;
	void	*ur_c;
	void	*d_w;
	void	*l_w;
	void	*r_w;
	void	*u_w;
};

struct s_pos
{
	int	x;
	int	y;
};

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	t_map			stats;
	struct s_images	images;
	t_list			***player;
	struct s_pos	*p_pos;
	t_list			**collect;
	struct s_pos	*c_pos;
	t_list			**exit;
	struct s_pos	*e_pos;

}	t_mlx;

char	*concat_str(char *memory, char *buf);
t_map	check_map(char *map, char **line);
void	free_dp(char **line);
void	map_error_handling(int error);
void	mlx_use(char **line, t_mlx *mlx);
void	error_handling(int error);
int		ft_rand(void);
void	mlx_load_images(void *mlx, struct s_images *images);
void	mlx_load_sprites(t_mlx *mlx, t_list **collect, t_list **exit);
int		animate_sprites(t_mlx *mlx);
void	save_pos(struct s_pos *pos, int x, int y);
void	malloc_sprites(t_mlx *mlx);
void	mlx_load_player(t_mlx *mlx, t_list ***player);

#endif
