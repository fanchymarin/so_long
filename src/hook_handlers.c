/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/27 12:44:59 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_next(t_mlx *mlx, t_pos *pos, t_pos new_pos)
{
	
	print(mlx, 0, pos->x, pos->y);
	print(mlx, 0, pos->x + new_pos.x, pos->y + new_pos.y);

}

void	move_player(t_mlx *mlx, t_list **sprite, t_pos *pos, t_pos new_pos)
{
	int	i;

	i = 0;
	if (!pos->image)
		pos->image = *sprite;
	while (i++ <= P_SPEED)
	{
		print_next(mlx, pos, new_pos);
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

void	stat_player(t_mlx *mlx, t_list **sprite, t_pos new_pos)
{
	int	i;

	i = 0;
	while (i < mlx->stats.p)
	{
		print(mlx, 0, mlx->p_pos[i].x, mlx->p_pos[i].y);
		print(mlx, (**sprite).content, mlx->p_pos[i].x, mlx->p_pos[i].y);
		if (mlx->line[mlx->p_pos[i].y + new_pos.y][mlx->p_pos[i].x
			+ new_pos.x] != '1' && mlx->line[mlx->p_pos[i].y + new_pos.y]
			[mlx->p_pos[i].x + new_pos.x] != 'P')
		{
			move_player(mlx, sprite, &mlx->p_pos[i], new_pos);
			if (mlx->p_pos[i].pixel_mov == PSIZE + 1
				|| mlx->p_pos[i].pixel_mov == ((PSIZE + 1) * -1))
			{
				mlx->p_pos[i].pixel_mov = 0;
				mlx->mov = 0;
				mlx->line[mlx->p_pos[i].y][mlx->p_pos[i].x] = '0';
				mlx->p_pos[i].x += new_pos.x;
				mlx->p_pos[i].y += new_pos.y;
				mlx->line[mlx->p_pos[i].y][mlx->p_pos[i].x] = 'P';
			}
		}
		++i;
	}
}

int	key_hook(int key, t_mlx *mlx)
{
	if (mlx->mov)
		return (0);
	if (key == KEY_S)
		mlx->mov = 'S';
	else if (key == KEY_A)
		mlx->mov = 'A';
	else if (key == KEY_W)
		mlx->mov = 'W';
	else if (key == KEY_D)
		mlx->mov = 'D';
	return (0);
}
