/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/22 20:15:11 by fmarin-p         ###   ########.fr       */
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

void	stat_player(t_mlx *mlx, t_list **sprite, int n_x, int n_y)
{
	int	i;
	int	rel_pos;
	int	x;
	int	y;
	static int	speed = 500;
	t_list	*image;

	i = 0;
	while (i < mlx->stats.p)
	{
		image = *sprite;
		x = mlx->p_pos[i].x;
		y = mlx->p_pos[i].y;
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, ret_f(mlx, x, y),
			x * PSIZE, y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			image->content, x * PSIZE, y * PSIZE);
		if (mlx->line[y + next_y][x + next_x] != '1')
		{
			rel_pos = 1;
			while (rel_pos <= PSIZE)
			{
				if (!image)
					image = *sprite;
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					ret_f(mlx, x, y), x * PSIZE, y * PSIZE);
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					ret_f(mlx, next_x, next_y), next_x * PSIZE, next_y * PSIZE);
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
			(**sprite).content, next_x * PSIZE, next_y * PSIZE);
		mlx->p_pos[i].x++;
		}
		++i;
	}	
}

int	key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_S)
		stat_player(mlx, mlx->player[0], 0, 1);
	else if (key == KEY_A)
		stat_player(mlx, mlx->player[1], -1, 0);
	else if (key == KEY_W)
		stat_player(mlx, mlx->player[2], 0, -1);
	else if (key == KEY_D)
		stat_player(mlx, mlx->player[3], 1, 0);
	return (0);
}
