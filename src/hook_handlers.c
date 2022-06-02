/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/02 19:15:09 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	finish_game(t_mlx *mlx __attribute__((unused)))
{
	exit(0);
	return (0);
}

void	reset_pos(t_mlx *mlx, t_list **sprite, t_pos *pos, t_pos new_pos)
{
	pos->image = 0;
	pos->pixel_mov = 0;
	mlx->mov = 0;
	if (mlx->line[pos->y + new_pos.y][pos->x + new_pos.x] == 'C')
		mlx->c_counter--;
	if (mlx->line[pos->y][pos->x] == 'B')
		mlx->line[pos->y][pos->x] = 'E';
	else
		mlx->line[pos->y][pos->x] = '0';
	pos->x += new_pos.x;
	pos->y += new_pos.y;
	if (mlx->line[pos->y][pos->x] != 'E')
		mlx->line[pos->y][pos->x] = 'P';
	else
		mlx->line[pos->y][pos->x] = 'B';
	print(mlx, 0, pos->x, pos->y);
	print(mlx, (**sprite).content, pos->x, pos->y);
}

void	stat_player(t_mlx *mlx, t_list **sprite, t_pos *pos, t_pos new_pos)
{
	int	i;

	i = 0;
	while (i < mlx->stats.p)
	{
		while (!pos[i].x && !pos[i].y && i != mlx->stats.p)
			++i;
		if (i == mlx->stats.p)
			break ;
		print(mlx, 0, pos[i].x, pos[i].y);
		print(mlx, (**sprite).content, pos[i].x, pos[i].y);
		if (mlx->line[pos[i].y + new_pos.y][pos[i].x + new_pos.x] != '1'
			&& mlx->line[pos[i].y + new_pos.y][pos[i].x + new_pos.x] != 'P')
		{
			move_player(mlx, sprite, &pos[i], new_pos);
			if (pos[i].pixel_mov > PSIZE || pos[i].pixel_mov < PSIZE * -1)
				reset_pos(mlx, sprite, &pos[i], new_pos);
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
	else if (key == KEY_ESC)
		finish_game(mlx);
	else
		return (0);
	mlx->last_dir = last_dir(key);
	return (0);
}

int	loop_hook(t_mlx *mlx)
{
	t_pos		new_pos;

	animate_c(mlx);
	animate_e(mlx);
	slime_ai(mlx);
	if (mlx->mov == 'S')
		stat_player(mlx, mlx->player[0], mlx->p_pos,
			new_pos = (t_pos){0, 1, 0, 0});
	else if (mlx->mov == 'A')
		stat_player(mlx, mlx->player[1], mlx->p_pos,
			new_pos = (t_pos){-1, 0, 0, 0});
	else if (mlx->mov == 'W')
		stat_player(mlx, mlx->player[2], mlx->p_pos,
			new_pos = (t_pos){0, -1, 0, 0});
	else if (mlx->mov == 'D')
		stat_player(mlx, mlx->player[3], mlx->p_pos,
			new_pos = (t_pos){1, 0, 0, 0});
	if (mlx->mov)
		stop_hook(mlx);
	return (0);
}
