/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:25:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/08 16:07:39 by fmarin-p         ###   ########.fr       */
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
	int	p_counter;
	int	c;
	int	s;
	int	height;
	int	width;

}	t_map;

typedef struct s_images
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
}	t_images;

typedef struct s_pos
{
	int		x;
	int		y;
	int		pixel_mov;
	t_list	*image;
	int		pos;
}	t_pos;

typedef struct s_new_pos
{
	int	x;
	int	y;
}	t_new_pos;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	char		**line;
	t_map		stats;
	t_images	images;
	t_list		***player;
	t_pos		*p_pos;
	t_list		**collect;
	t_pos		*c_pos;
	t_list		**exit;
	t_pos		*e_pos;
	t_list		***slime;
	t_pos		*s_pos;
	char		**f_pos;
	char		mov;
	int			last_dir;
	int			counter;
	int			c_counter;
	int			stat;
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
void	mlx_load_slime(t_mlx *mlx, t_list ***slime);
void	mlx_load_player(t_mlx *mlx, t_list ***player);
void	mlx_render_floor(t_mlx *mlx, int width, int height);
int		animate_sprites(t_mlx *mlx);
void	save_pos(struct s_pos *pos, int x, int y);
void	malloc_sprites(t_mlx *mlx);
void	store_f_pos(t_mlx *mlx, int x, int y, int id);
void	*ret_f(t_mlx *mlx, int x, int y);
int		key_hook(int key, t_mlx *mlx);
int		loop_hook(t_mlx *mlx);
void	animate_e(t_mlx *mlx);
void	animate_c(t_mlx *mlx);
void	stat_player(t_mlx *mlx, t_list **sprite, t_pos *pos, t_new_pos new_pos);
void	print(t_mlx *mlx, void *image, int x, int y);
void	move_player(t_mlx *mlx, t_list **sprite, t_pos *pos, t_new_pos new_pos);
void	struct_init(t_mlx *mlx);
int		last_dir(int key);
void	stop_hook(t_mlx *mlx);
int		finish_game(t_mlx *mlx);
void	mlx_render_walls(t_mlx *mlx, int width, int height, int x);
t_pos	*find_player(t_mlx *mlx, t_pos e_pos);
void	slime_ai(t_mlx *mlx, t_list ***slime, t_pos *pos);

#endif
