/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/23 21:35:01 by fmarin-p         ###   ########.fr       */
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

void	move_player(t_mlx *mlx, t_list **sprite, t_pos pos, t_pos new_pos)
{
	int			pixel_mov;
	static int	speed = 500;
	t_list		*image;

	pixel_mov = 1;
	image = *sprite;
	while (pixel_mov <= PSIZE)
	{
		if (!image)
			image = *sprite;
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			ret_f(mlx, pos.x, pos.y), pos.x * PSIZE, pos.y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			ret_f(mlx, pos.x + new_pos.x, pos.y + new_pos.y),
			pos.x + new_pos.x * PSIZE, pos.y + new_pos.y * PSIZE);
		if (new_pos.x)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				image->content, (pos.x * PSIZE) + pixel_mov, pos.y * PSIZE);
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				image->content, pos.x * PSIZE, (pos.y * PSIZE) + pixel_mov);
		if (!speed--)
		{
			pixel_mov++;
			image = image->next;
			speed = 500;
		}
	}
}

void	stat_player(t_mlx *mlx, t_list **sprite, t_pos new_pos)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	while (i < mlx->stats.p)
	{
		x = mlx->p_pos[i].x;
		y = mlx->p_pos[i].y;
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, ret_f(mlx, x, y),
			x * PSIZE, y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			(*sprite)->content, x * PSIZE, y * PSIZE);
		if (mlx->line[y + new_pos.y][x + new_pos.x] != '1')
		{
			move_player(mlx, sprite, *mlx->p_pos, new_pos);
			mlx->p_pos[i].x += new_pos.x;
			mlx->p_pos[i].y += new_pos.y;
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				(**sprite).content, mlx->p_pos[i].x * PSIZE,
				mlx->p_pos[i].y * PSIZE);
		}
		++i;
	}	
}

int	key_hook(int key, t_mlx *mlx)
{
	t_pos	new_pos;

	if (key == KEY_S)
	{
		new_pos = (t_pos){0, 1};
		stat_player(mlx, mlx->player[0], new_pos);
	}
	else if (key == KEY_A)
	{
		new_pos = (t_pos){-1, 0};
		stat_player(mlx, mlx->player[1], new_pos);
	}
	else if (key == KEY_W)
	{
		new_pos = (t_pos){0, -1};
		stat_player(mlx, mlx->player[2], new_pos);
	}
	else if (key == KEY_D)
	{
		new_pos = (t_pos){1, 0};
		stat_player(mlx, mlx->player[3], new_pos);
	}
	return (0);
}
