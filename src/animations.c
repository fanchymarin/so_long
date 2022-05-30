/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student-42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:30:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/27 12:34:59 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			print(mlx, (**mlx->player[mlx->last_dir]).content,
				mlx->e_pos[i].x, mlx->e_pos[i].y);
		i++;
	}
	if (!speed--)
	{
		exit = exit->next;
		speed = E_SPEED;
	}
}
