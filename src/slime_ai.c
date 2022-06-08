/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:21:46 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/08 16:11:12 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	*init_speed(t_mlx *mlx)
{
	int	i;
	int	*speed;

	speed = (int *) malloc(sizeof(int) * mlx->stats.s);
	i = 0;
	while (i < mlx->stats.s)
		speed[i++] = S_SPEED;
	return (speed);
}

void	stat_slime(t_mlx *mlx, t_list ***slime, t_pos *s_pos)
{
	static int	*speed = 0;
	int			i;

	i = 0;
	if (!speed)
		speed = init_speed(mlx);
	while (i < mlx->stats.s)
	{
		if (s_pos[i].pixel_mov)
			++i;
		if (i >= mlx->stats.s)
			break ;
		if (!s_pos[i].image)
			s_pos[i].image = *slime[s_pos[i].pos];
		print(mlx, 0, s_pos[i].x, s_pos[i].y);
		print(mlx, s_pos[i].image->content, s_pos[i].x, s_pos[i].y);
		if (!speed[i]--)
		{
			s_pos[i].image = s_pos[i].image->next;
			speed[i] = S_SPEED;
		}
		++i;
	}
}

t_new_pos	random_dir(int *pos)
{
	int	num;

	num = ft_rand() % 4;
	if (num == 0 || num == 1)
	{
		*pos = 0;
		if (!num)
			return ((t_new_pos) {0, 1});
		if (num == 1)
			return ((t_new_pos) {-1, 0});
	}
	else if (num == 2 || num == 3)
	{
		*pos = 1;
		if (num == 2)
			return ((t_new_pos) {0, -1});
		if (num == 3)
			return ((t_new_pos) {1, 0});
	}
	return ((t_new_pos) {0, 0});
}

void	move_slime(t_mlx *mlx, t_list **sprite, t_pos *pos, t_new_pos npos)
{
	static int	*speed = 0;
	static int	i = 0;

	if (!speed)
		speed = init_speed(mlx);
	if (!pos->image)
		pos->image = *sprite;
	print(mlx, 0, pos->x, pos->y);
	if (mlx->line[pos->y + npos.y][pos->x + npos.x] == '0')
	{
		print(mlx, 0, pos->x + npos.x, pos->y + npos.y);
		if (npos.x)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, pos->image->content,
				(pos->x * PSIZE) + pos->pixel_mov, pos->y * PSIZE);
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, pos->image->content,
				pos->x * PSIZE, (pos->y * PSIZE) + pos->pixel_mov);
		if (npos.x == 1 || npos.y == 1)
			pos->pixel_mov++;
		else
			pos->pixel_mov--;
		if (pos->pixel_mov > PSIZE || pos->pixel_mov < PSIZE * -1)
		{
			mlx->line[pos->y][pos->x] = '0';
			pos->y += npos.y;
			pos->x += npos.x;
			mlx->line[pos->y][pos->x] = 'S';
		}
	}
	else
		print(mlx, pos->image->content, pos->x, pos->y);
	if (!speed[i]--)
	{
		pos->image = pos->image->next;
		speed[i] = S_SPEED;
	}
	if (++i >= mlx->stats.s)
		i = 0;
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
	static int			stat = 50;
	static t_new_pos	*npos = 0;
	int					i;

	if (!npos)
		npos = (t_new_pos *) ft_calloc(sizeof(t_new_pos), mlx->stats.s);
	if (stat)
	{
		stat_slime(mlx, slime, s_pos);
		--stat;
		return ;
	}
	i = 0;
	while (i < mlx->stats.s)
	{
		if (!npos[i].x && !npos[i].y)
			npos[i] = random_dir(&s_pos[i].pos);
		move_slime(mlx, slime[s_pos[i].pos], &s_pos[i], npos[i]);
		i++;
	}
	if (stop_s_hook(mlx, mlx->s_pos))
	{
		stat = 50;
		ft_bzero(npos, sizeof(t_new_pos) * mlx->stats.s);
	}
}
