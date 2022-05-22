/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/22 19:10:03 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_c(t_mlx *mlx)
{
	static t_list	*collect = 0;
	static int		speed = 6000;
	int				i;

	if (!collect)
		collect = (*mlx->collect);
	i = 0;
	while (i < mlx->stats.c)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			ret_f(mlx, mlx->c_pos[i].x, mlx->c_pos[i].y), mlx->c_pos[i].x
			* PSIZE, mlx->c_pos[i].y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			collect->content, mlx->c_pos[i].x * PSIZE,
			mlx->c_pos[i].y * PSIZE);
		i++;
	}
	if (!speed--)
	{
		collect = collect->next;
		speed = 6000;
	}
}

void	animate_e(t_mlx *mlx)
{
	static t_list	*exit = 0;
	int				i;

	if (!exit)
		exit = (*mlx->exit);
	i = 0;
	while (i < mlx->stats.e)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			ret_f(mlx, mlx->e_pos[i].x, mlx->e_pos[i].y), mlx->e_pos[i].x
			* PSIZE, mlx->e_pos[i].y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			exit->content, mlx->e_pos[i].x * PSIZE, mlx->e_pos[i].y * PSIZE);
		i++;
	}
	exit = exit->next;
}

int	animate_sprites(t_mlx *mlx)
{
	animate_c(mlx);
	animate_e(mlx);
	return (0);
}

int	key_hook(int key, t_mlx *mlx)
{
	int	i;
	int	rel_pos;
	int	x;
	int	y;
	static int	speed = 500;
	t_list	*image;

	i = 0;
	if (key == KEY_D)
	{
		while (i < mlx->stats.p)
		{
			image = *mlx->player[3];
			x = mlx->p_pos[i].x;
			y = mlx->p_pos[i].y;
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, ret_f(mlx, x, y),
					x * PSIZE, y * PSIZE);
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					image->content, x * PSIZE, y * PSIZE);
			if (mlx->line[y][x + 1] != '1')
			{
				rel_pos = 1;
				while (rel_pos <= PSIZE)
				{
					if (!image)
						image = *mlx->player[3];
					mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
							ret_f(mlx, x, y), x * PSIZE, y * PSIZE);
					mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
							ret_f(mlx, x + 1, y), (x + 1) * PSIZE, y * PSIZE);
					mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
						image->content, (x * PSIZE) + rel_pos, y * PSIZE);
					if (!speed--)
					{
						rel_pos++;
						image = image->next;
						speed = 500;
					}
				}
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				(**mlx->player[3]).content, (x + 1) * PSIZE, y * PSIZE);
			mlx->p_pos[i].x++;
			}
			++i;
		}	
	}
	return (0);
}
