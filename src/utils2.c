/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:14:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/01 17:34:19 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	last_dir(int key)
{
	if (key == KEY_S)
		return (0);
	else if (key == KEY_A)
		return (1);
	else if (key == KEY_W)
		return (2);
	else if (key == KEY_D)
		return (3);
	return (0);
}

void	*ret_f(t_mlx *mlx, int x, int y)
{
	if (mlx->f_pos[y][x] == 1)
		return (mlx->images.f1);
	else if (mlx->f_pos[y][x] == 2)
		return (mlx->images.f2);
	else
		return (mlx->images.f3);
}

void	stop_hook(t_mlx *mlx)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < mlx->stats.p)
		check += mlx->p_pos[i++].pixel_mov;
	if (!check)
		mlx->mov = 0;
	else
	{
		mlx->counter++;
		if (mlx->counter % PSIZE == 0)
		{
			mlx_render_walls(mlx, mlx->stats.width - 1,
				mlx->stats.height - 1, PSIZE);
			mlx_string_put(mlx->mlx, mlx->mlx_win, mlx->stats.width
				* PSIZE / 2, mlx->stats.height * PSIZE, 16777215,
				ft_itoa(mlx->counter / PSIZE));
		}
	}
}

void	print(t_mlx *mlx, void *image, int x, int y)
{
	if (!image)
		mlx_put_image_to_window(mlx->mlx,
			mlx->mlx_win, ret_f(mlx, x, y), x * PSIZE, y * PSIZE);
	else
		mlx_put_image_to_window(mlx->mlx,
			mlx->mlx_win, image, x * PSIZE, y * PSIZE);
}

void	struct_init(t_mlx *mlx)
{
	mlx->mov = 0;
	mlx->counter = 0;
	mlx->c_counter = mlx->stats.c;
	mlx->f_pos = 0;
}
