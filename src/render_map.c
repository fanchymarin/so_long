/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:35:49 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/19 20:54:04 by fmarin-p         ###   ########.fr       */
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

void	mlx_render_rocks(t_mlx *mlx, char **line, int x, int y)
{
	int	r;

	while (line[y + 1])
	{
		x = 1;
		while (line[y + 1][x + 1])
		{
			if (line[y][x] == '1')
			{
				r = ft_rand();
				if (r % 2 == 0)
					mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
						mlx->images.r1, x * PSIZE, y * PSIZE);
				else if (r % 3 == 0)
					mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
						mlx->images.r2, x * PSIZE, y * PSIZE);
				else
					mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
						mlx->images.r3, x * PSIZE, y * PSIZE);
			}
			++x;
		}
		++y;
	}
}

int	animate_c(t_mlx *mlx)
{
	static	t_list	*start = 0;

	usleep(70000);
	if (!start)
		start = (*mlx->collect);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
		start->content, mlx->c_x * PSIZE, mlx->c_y * PSIZE);
	start = start->next;
	return (0);
}

void	mlx_render_sprites(t_mlx *mlx, char **line)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (line[y + 1])
	{
		x = 1;
		while (line[y + 1][x + 1])
		{
			if (line[y][x] == 'C')
			{
				mlx->c_x = x;
				mlx->c_y = y;
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					(**mlx->collect).content, x * PSIZE, y * PSIZE);
			}
			else if (line[y][x] == 'E')
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					(**mlx->exit).content, x * PSIZE, y * PSIZE);
			++x;
		}
		++y;
	}
	mlx_loop_hook(mlx->mlx, animate_c, mlx);
}

void	mlx_use(char **line, t_map stats)
{
	t_mlx		mlx;

	mlx = (t_mlx){.player = malloc(sizeof(t_list *)),
		.collect = malloc(sizeof(t_list *)),
		.exit = malloc(sizeof(t_list *))};
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, PSIZE * stats.width,
			PSIZE * (stats.height + 1), "so_long");
	if (!mlx.mlx || !mlx.mlx_win)
		error_handling(4);
	mlx_mouse_hide();
	mlx_load_images(mlx.mlx, &mlx.images);
	mlx_load_sprites(mlx.mlx, mlx.collect, mlx.exit);
	mlx_render_floor(&mlx, stats.width, stats.height);
	mlx_render_walls(&mlx, stats.width - 1, stats.height - 1, PSIZE);
	mlx_render_rocks(&mlx, line, 1, 1);
	mlx_render_sprites(&mlx, line);
	mlx_loop(mlx.mlx);
}
