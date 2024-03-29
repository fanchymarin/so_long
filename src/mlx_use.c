/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_use.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:35:49 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/05 13:13:45 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_render_floor(t_mlx *mlx, int width, int height)
{
	int	x;
	int	y;
	int	r;

	y = 1;
	while (y <= height - 2)
	{
		x = 0;
		while (x <= width - 1)
		{
			r = ft_rand() % 3;
			if (r == 0)
				store_f_pos(mlx, x, y, 1);
			else if (r == 1)
				store_f_pos(mlx, x, y, 3);
			else if (r == 2)
				store_f_pos(mlx, x, y, 2);
			x++;
		}
		y++;
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
				r = ft_rand() % 3;
				if (r == 0)
					print(mlx, mlx->images.r1, x, y);
				else if (r == 1)
					print(mlx, mlx->images.r2, x, y);
				else if (r == 2)
					print(mlx, mlx->images.r3, x, y);
			}
			++x;
		}
		++y;
	}
}

void	mlx_render_sprites(t_mlx *mlx, char **line, int x, int y)
{
	int	*counter;

	counter = (int *) ft_calloc(sizeof(int), 4);
	while (line[y + 1])
	{
		x = 1;
		while (line[y + 1][x + 1])
		{
			if (line[y][x] == 'C')
				save_pos(&mlx->c_pos[counter[0]++], x, y);
			else if (line[y][x] == 'E')
				save_pos(&mlx->e_pos[counter[1]++], x, y);
			else if (line[y][x] == 'P')
			{
				save_pos(&mlx->p_pos[counter[2]++], x, y);
				print(mlx, (**mlx->player[0]).content, x, y);
			}
			else if (line[y][x] == 'S')
				save_pos(&mlx->s_pos[counter[3]++], x, y);
			++x;
		}
		++y;
	}
	free(counter);
}

void	mlx_use(char **line, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, PSIZE * mlx->stats.width,
			PSIZE * (mlx->stats.height + 1), "so_long");
	if (!mlx->mlx || !mlx->mlx_win)
		error_handling(4);
	malloc_sprites(mlx);
	struct_init(mlx);
	mlx_load_images(mlx->mlx, &mlx->images);
	mlx_load_sprites(mlx, mlx->collect, mlx->exit);
	mlx_load_player(mlx, mlx->player);
	mlx_load_slime(mlx, mlx->slime);
	mlx_render_floor(mlx, mlx->stats.width, mlx->stats.height);
	mlx_render_walls(mlx, mlx->stats.width - 1, mlx->stats.height - 1, PSIZE);
	mlx_render_rocks(mlx, line, 1, 1);
	mlx_render_sprites(mlx, line, 1, 1);
	mlx_loop_hook(mlx->mlx, loop_hook, mlx);
	mlx_key_hook(mlx->mlx_win, key_hook, mlx);
	mlx_hook(mlx->mlx_win, 17, 0, finish_game, mlx);
	mlx_loop(mlx->mlx);
}
