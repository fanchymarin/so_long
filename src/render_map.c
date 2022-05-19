/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:35:49 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/19 15:23:57 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_render_floor(t_mlx *mlx, int width, int height)
{
	int	x;
	int	y;
	int	r;

	y = PSIZE;
	while (y / PSIZE <= height - 2)
	{
		x = 0;
		while (x / PSIZE <= width)
		{
			r = ft_rand();
			if (r % 2 == 0)
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					mlx->images.f1, x, y);
			else if (r % 3 == 0)
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					mlx->images.f3, x, y);
			else
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					mlx->images.f2, x, y);
			x += PSIZE;
		}
		y += PSIZE;
	}
}

void	mlx_render_walls(t_mlx *mlx, int width, int height, int x)
{
	int	y;

	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.ul_c, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.ur_c,
		PSIZE * width, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.dl_c,
		0, PSIZE * height);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.dr_c,
		PSIZE * width, PSIZE * height);
	while (x / PSIZE < width)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.u_w, x, 0);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.d_w,
			x, PSIZE * height);
		x += PSIZE;
	}
	y = PSIZE;
	while (y / PSIZE < height)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.l_w, 0, y);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.r_w,
			PSIZE * width, y);
		y += PSIZE;
	}
}

void	mlx_use(char **line, t_map stats)
{
	t_mlx	mlx;
//	t_list	**player;
	t_list	**collect;
	t_list	**exit;

	(void) line;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, PSIZE * stats.width,
			PSIZE * (stats.height + 1), "so_long");
	if (!mlx.mlx || !mlx.mlx_win)
		error_handling(4);
	mlx_mouse_hide();
	mlx_load_images(mlx.mlx, &mlx.images);
	collect = 0;
	exit = 0;
//	mlx_load_sprites(mlx.mlx, collect, exit);
	mlx_render_floor(&mlx, stats.width, stats.height);
	mlx_render_walls(&mlx, stats.width - 1, stats.height - 1, PSIZE);
	mlx_loop(mlx.mlx);
}
