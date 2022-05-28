/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:14:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/26 15:33:24 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			printf("%d\n", mlx->counter / PSIZE);
	}
}

int	animate_sprites(t_mlx *mlx)
{
	t_pos		new_pos;

	animate_c(mlx);
	animate_e(mlx);
	if (mlx->mov == 'S')
		stat_player(mlx, mlx->player[0], new_pos = (t_pos){0, 1, 0, 0});
	else if (mlx->mov == 'A')
		stat_player(mlx, mlx->player[1], new_pos = (t_pos){-1, 0, 0, 0});
	else if (mlx->mov == 'W')
		stat_player(mlx, mlx->player[2], new_pos = (t_pos){0, -1, 0, 0});
	else if (mlx->mov == 'D')
		stat_player(mlx, mlx->player[3], new_pos = (t_pos){1, 0, 0, 0});
	if (mlx->mov)
		stop_hook(mlx);
	return (0);
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
