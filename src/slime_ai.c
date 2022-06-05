/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:22:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/05 17:23:04 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_s(t_mlx *mlx, t_list **sprite, t_pos *pos, t_pos new_pos)
{
	static int	speed = S_SPEED;

	if (!pos->image)
		pos->image = *sprite;
	print(mlx, 0, pos->x, pos->y);
	if (mlx->line[pos->y + new_pos.y][pos->x + new_pos.x] == '0' && !new_pos.pos)
	{
		print(mlx, 0, pos->x + new_pos.x, pos->y + new_pos.y);
		if (new_pos.x)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, pos->image->content,
				(pos->x * PSIZE) + pos->pixel_mov, pos->y * PSIZE);
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, pos->image->content,
				pos->x * PSIZE, (pos->y * PSIZE) + pos->pixel_mov);
		if (new_pos.x == 1 || new_pos.y == 1)
			pos->pixel_mov++;
		else
			pos->pixel_mov--;
		if (pos->pixel_mov > PSIZE || pos->pixel_mov < PSIZE * -1)
		{
			mlx->line[pos->y][pos->x] = '0';
			pos->y += new_pos.y;
			pos->x += new_pos.x;
			mlx->line[pos->y][pos->x] = 'S';
		}
	}
	else
		print(mlx, pos->image->content, pos->x, pos->y);
	if (!speed--)
	{
		pos->image = pos->image->next;
		speed = S_SPEED * mlx->stats.s;
	}
}

int	stop_s_hook(t_mlx *mlx, t_pos *s_pos)
{
	int			i;
	int			check;
	static int	reset = 0;

	i = 0;
	check = 0;
	while (i < mlx->stats.s)
	{
		if (s_pos[i].pixel_mov > PSIZE || s_pos[i].pixel_mov < PSIZE * -1)
		{
			check++;
			s_pos[i].pixel_mov = 0;
			s_pos[i].image = 0;
		}
		i++;
	}
	if (!check)
		++reset;
	if (reset > PSIZE * 3)
	{
		reset = 0;
		return (1);
	}
	return (check);
}

void	slime_ai(t_mlx *mlx, t_list ***slime, t_pos *s_pos)
{
	static int	*dir = 0;
	static int	speed = 50;
	t_pos		new_pos;
	int			i;

	if (speed)
	{
		i = 0;
		while (i < mlx->stats.s)
		{
			animate_s(mlx, slime[s_pos[i].pos],
				&s_pos[i], (t_pos){0, 0, 0, 0, 1});
			++i;
		}
		speed--;
		return ;
	}
	if (!dir)
		dir = (int *) ft_calloc(sizeof(int), mlx->stats.s);
	i = 0;
	while (i < mlx->stats.s)
	{
		if (!dir[i])
			dir[i] = ft_rand() % 4;
		if (dir[i] == 0)
		{
			s_pos[i].pos = 0;
			new_pos = (t_pos){0, 1, 0, 0, 0};
		}
		else if (dir[i] == 1)
		{
			s_pos[i].pos = 0;
			new_pos = (t_pos){-1, 0, 0, 0, 0};
		}
		else if (dir[i] == 2)
		{
			s_pos[i].pos = 1;
			new_pos = (t_pos){0, -1, 0, 0, 0};
		}
		else if (dir[i] == 3)
		{
			s_pos[i].pos = 1;
			new_pos = (t_pos){1, 0, 0, 0, 0};
		}
		animate_s(mlx, slime[s_pos[i].pos], &s_pos[i], new_pos);
		++i;
	}
	if (stop_s_hook(mlx, mlx->s_pos))
	{
		speed = 50;
		ft_bzero(dir, sizeof(int) * mlx->stats.s);
	}
}
