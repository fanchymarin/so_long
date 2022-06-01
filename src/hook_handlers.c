/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/01 17:14:36 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->images.f1);
	mlx_destroy_image(mlx->mlx, mlx->images.f2);
	mlx_destroy_image(mlx->mlx, mlx->images.f3);
	mlx_destroy_image(mlx->mlx, mlx->images.r1);
	mlx_destroy_image(mlx->mlx, mlx->images.r2);
	mlx_destroy_image(mlx->mlx, mlx->images.r3);
	mlx_destroy_image(mlx->mlx, mlx->images.dl_c);
	mlx_destroy_image(mlx->mlx, mlx->images.dr_c);
	mlx_destroy_image(mlx->mlx, mlx->images.ul_c);
	mlx_destroy_image(mlx->mlx, mlx->images.ur_c);
	mlx_destroy_image(mlx->mlx, mlx->images.d_w);
	mlx_destroy_image(mlx->mlx, mlx->images.l_w);
	mlx_destroy_image(mlx->mlx, mlx->images.r_w);
	mlx_destroy_image(mlx->mlx, mlx->images.u_w);
}

void	destroy_sprites(t_mlx *mlx, t_list **sprite)
{
	t_list	*tmp;

	while (*sprite)
	{
		tmp = (*sprite)->next;
		mlx_destroy_image(mlx->mlx, (*sprite)->content);
		free(*sprite);
		*sprite = tmp;
	}
	free(sprite);
}

int	finish_game(t_mlx *mlx)
{
	int	i;

	i = 0;
	destroy_images(mlx);
	destroy_sprites(mlx, mlx->collect);
	destroy_sprites(mlx, mlx->exit);
	free_dp(mlx->line);
	free_dp(mlx->f_pos);
	free(mlx->c_pos);
	free(mlx->e_pos);
	free(mlx->p_pos);
	while (i < 4)
		destroy_sprites(mlx, mlx->player[i++]);
	free(mlx->player);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	free(mlx->mlx);
	exit(0);
	return (0);
}

void	reset_pos(t_mlx *mlx, t_pos *pos, t_pos new_pos)
{
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
}

void	stat_player(t_mlx *mlx, t_list **sprite, t_pos new_pos)
{
	int	i;

	i = 0;
	while (i < mlx->stats.p)
	{
		while (!mlx->p_pos[i].x && !mlx->p_pos[i].y && i != mlx->stats.p)
			++i;
		if (i == mlx->stats.p)
			break ;
		print(mlx, 0, mlx->p_pos[i].x, mlx->p_pos[i].y);
		print(mlx, (**sprite).content, mlx->p_pos[i].x, mlx->p_pos[i].y);
		if (mlx->line[mlx->p_pos[i].y + new_pos.y][mlx->p_pos[i].x
			+ new_pos.x] != '1' && mlx->line[mlx->p_pos[i].y + new_pos.y]
			[mlx->p_pos[i].x + new_pos.x] != 'P')
		{
			move_player(mlx, sprite, &mlx->p_pos[i], new_pos);
			if (mlx->p_pos[i].pixel_mov > PSIZE
				|| mlx->p_pos[i].pixel_mov < PSIZE * -1)
			{
				reset_pos(mlx, &mlx->p_pos[i], new_pos);
				print(mlx, 0, mlx->p_pos[i].x, mlx->p_pos[i].y);
				print(mlx, (**sprite).content,
					mlx->p_pos[i].x, mlx->p_pos[i].y);
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
