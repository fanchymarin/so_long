/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:35:49 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/18 13:51:25 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_load_images(void *mlx, struct s_images *images)
{
	int		a;
	int		b;

	images->f1 = mlx_xpm_file_to_image(mlx, "./assets/0/f1.xpm", &a, &b);
	images->f2 = mlx_xpm_file_to_image(mlx, "./assets/0/f2.xpm", &a, &b);
	images->f3 = mlx_xpm_file_to_image(mlx, "./assets/0/f3.xpm", &a, &b);
	images->r1 = mlx_xpm_file_to_image(mlx, "./assets/1-1/r1.xpm", &a, &b);
	images->r2 = mlx_xpm_file_to_image(mlx, "./assets/1-1/r2.xpm", &a, &b);
	images->r3 = mlx_xpm_file_to_image(mlx, "./assets/1-1/r3.xpm", &a, &b);
	images->dl_c = mlx_xpm_file_to_image(mlx, "./assets/1/dl_c.xpm", &a, &b);
	images->dr_c = mlx_xpm_file_to_image(mlx, "./assets/1/dr_c.xpm", &a, &b);
	images->ul_c = mlx_xpm_file_to_image(mlx, "./assets/1/ul_c.xpm", &a, &b);
	images->ur_c = mlx_xpm_file_to_image(mlx, "./assets/1/ur_c.xpm", &a, &b);
	images->d_w = mlx_xpm_file_to_image(mlx, "./assets/1/d_w.xpm", &a, &b);
	images->l_w = mlx_xpm_file_to_image(mlx, "./assets/1/l_w.xpm", &a, &b);
	images->r_w = mlx_xpm_file_to_image(mlx, "./assets/1/r_w.xpm", &a, &b);
	images->u_w = mlx_xpm_file_to_image(mlx, "./assets/1/u_w.xpm", &a, &b);
}

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
			r = rand();
			if (r % 2 == 0)
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
										mlx->images.f1, x, y);
			else if (r % 3 == 0)
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
										mlx->images.f2, x, y);
			else
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
										mlx->images.f3, x, y);
			x += PSIZE;
		}
		y += PSIZE;
	}
}

void	mlx_render_walls(t_mlx *mlx, int width, int height)
{
	int	x;
	int	y;

	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.ul_c, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.ur_c,
							PSIZE * width, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.dl_c,
							0, PSIZE * height);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.dr_c,
							PSIZE * width, PSIZE * height);
	x = PSIZE;
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
	(void) line;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, PSIZE * stats.width, 
								PSIZE * (stats.height + 1), "so_long");
	if (!mlx.mlx || !mlx.mlx_win)
		error_handling(4);
	mlx_load_images(mlx.mlx, &mlx.images);
	mlx_render_floor(&mlx, stats.width, stats.height);
	mlx_render_walls(&mlx, stats.width - 1, stats.height - 1);
	mlx_loop(mlx.mlx);
}
