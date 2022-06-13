/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:21:46 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/10 13:23:32 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	still_slime(t_mlx *mlx, t_list ***slime, t_pos *s_pos)
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

void	move_slime(t_mlx *mlx, t_pos *pos, t_new_pos npos)
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
	if (mlx->line[pos->y + npos.y][pos->x + npos.x] == 'P')
	{
		print(mlx, (*mlx->player[mlx->last_dir])->content,
			pos->x + npos.x, pos->y + npos.y);
		if (pos->pixel_mov > PSIZE / 2 || pos->pixel_mov < PSIZE / -2)
			finish_game(mlx);
	}
	if (pos->pixel_mov > PSIZE || pos->pixel_mov < PSIZE * -1)
	{
		mlx->line[pos->y][pos->x] = '0';
		pos->y += npos.y;
		pos->x += npos.x;
		mlx->line[pos->y][pos->x] = 'S';
	}
}

void	stat_slime(t_mlx *mlx, t_list **sprite, t_pos *pos, t_new_pos npos)
{
	static int	*speed = 0;
	static int	i = 0;

	if (!speed)
		speed = init_speed(mlx);
	if (!pos->image)
		pos->image = *sprite;
	print(mlx, 0, pos->x, pos->y);
	if (mlx->line[pos->y + npos.y][pos->x + npos.x] == '0'
		|| mlx->line[pos->y + npos.y][pos->x + npos.x] == 'P')
		move_slime(mlx, pos, npos);
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
	int			check_mov;
	int			check_stat;

	i = 0;
	check_mov = 0;
	check_stat = 0;
	while (i < mlx->stats.s)
	{
		if (s_pos[i].pixel_mov > PSIZE || s_pos[i].pixel_mov < PSIZE * -1)
		{
			check_mov++;
			s_pos[i].pixel_mov = 0;
			s_pos[i].image = 0;
		}
		else if (!s_pos[i].pixel_mov)
			check_stat++;
		i++;
	}
	if (check_stat == mlx->stats.s)
		return (1);
	return (check_mov);
}

void	slime_ai(t_mlx *mlx, t_list ***slime, t_pos *s_pos)
{
	static int			still = 70;
	static t_new_pos	*npos = 0;
	int					i;

	if (!npos)
		npos = (t_new_pos *) ft_calloc(sizeof(t_new_pos), mlx->stats.s);
	if (still)
	{
		still_slime(mlx, slime, s_pos);
		--still;
		return ;
	}
	i = 0;
	while (i < mlx->stats.s)
	{
		if (!npos[i].x && !npos[i].y)
			npos[i] = random_dir(&s_pos[i].pos);
		stat_slime(mlx, slime[s_pos[i].pos], &s_pos[i], npos[i]);
		i++;
	}
	if (stop_s_hook(mlx, mlx->s_pos))
	{
		still = 70;
		ft_bzero(npos, sizeof(t_new_pos) * mlx->stats.s);
	}
}
