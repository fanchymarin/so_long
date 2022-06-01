/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:30:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/01 16:40:15 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_player(t_mlx *mlx, struct s_pos *p_pos)
{
	static int	i = 0;
	static int	speed = END_SPEED;

	mlx->mov = 'E';
	print(mlx, (*mlx->player[i++])->content, p_pos->x, p_pos->y);
	if (i == 4)
		i = 0;
	if (!speed--)
	{
		mlx->line[p_pos->y][p_pos->x] = 'E';
		p_pos->x = 0;
		p_pos->y = 0;
		mlx->mov = 0;
		speed = END_SPEED;
		mlx->stats.p_counter--;
	}
	if (!mlx->stats.p_counter)
		finish_game(mlx);
}

void	print_path(t_mlx *mlx, t_pos *pos, t_pos new_pos)
{
	print(mlx, 0, pos->x, pos->y);
	print(mlx, 0, pos->x + new_pos.x, pos->y + new_pos.y);
	if (mlx->line[pos->y][pos->x] == 'B'
		|| mlx->line[pos->y + new_pos.y][pos->x + new_pos.x] == 'E')
		animate_e(mlx);
	if (mlx->line[pos->y + new_pos.y][pos->x + new_pos.x] == 'C')
		animate_c(mlx);
}

void	move_player(t_mlx *mlx, t_list **sprite, t_pos *pos, t_pos new_pos)
{
	int	i;

	i = 0;
	if (!pos->image)
		pos->image = *sprite;
	while (i++ <= P_SPEED)
	{
		print_path(mlx, pos, new_pos);
		if (new_pos.x)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, pos->image->content,
				(pos->x * PSIZE) + pos->pixel_mov, pos->y * PSIZE);
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, pos->image->content,
				pos->x * PSIZE, (pos->y * PSIZE) + pos->pixel_mov);
	}
	if (new_pos.x == 1 || new_pos.y == 1)
		pos->pixel_mov++;
	else
		pos->pixel_mov--;
	if (pos->pixel_mov % 4 == 0)
		pos->image = pos->image->next;
}

void	animate_c(t_mlx *mlx)
{
	static t_list	*collect = 0;
	static int		speed = C_SPEED;
	int				i;

	if (!collect)
		collect = (*mlx->collect);
	i = 0;
	while (i < mlx->stats.c)
	{
		if (mlx->line[mlx->c_pos[i].y][mlx->c_pos[i].x] == 'C')
		{
			print(mlx, 0, mlx->c_pos[i].x, mlx->c_pos[i].y);
			print(mlx, collect->content, mlx->c_pos[i].x, mlx->c_pos[i].y);
		}
		i++;
	}
	if (!speed--)
	{
		collect = collect->next;
		speed = C_SPEED;
	}
}

struct s_pos	*find_player(t_mlx *mlx, struct s_pos e_pos)
{
	int	i;

	i = 0;
	while (i < mlx->stats.p)
	{
		if (mlx->p_pos[i].y == e_pos.y && mlx->p_pos[i].x == e_pos.x)
			break ;
		++i;
	}
	return (&mlx->p_pos[i]);
}

void	animate_e(t_mlx *mlx)
{
	static t_list	*exit = 0;
	static int		speed = E_SPEED;
	int				i;

	if (!exit)
		exit = (*mlx->exit);
	i = 0;
	while (i < mlx->stats.e)
	{
		print(mlx, 0, mlx->e_pos[i].x, mlx->e_pos[i].y);
		print(mlx, exit->content, mlx->e_pos[i].x, mlx->e_pos[i].y);
		if (mlx->line[mlx->e_pos[i].y][mlx->e_pos[i].x] == 'B' && !mlx->mov)
		{
			if (mlx->c_counter)
				print(mlx, (**mlx->player[mlx->last_dir]).content,
					mlx->e_pos[i].x, mlx->e_pos[i].y);
			else
				exit_player(mlx, find_player(mlx, mlx->e_pos[i]));
		}
		i++;
	}
	if (!speed--)
	{
		exit = exit->next;
		speed = E_SPEED;
	}
}
