/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:46:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/09 13:32:04 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pos	*find_player(t_mlx *mlx, t_pos e_pos)
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

t_new_pos	random_dir(int *pos)
{
	int	num;

	num = ft_rand() % 4;
	if (num == 0 || num == 1)
	{
		*pos = 0;
		if (!num)
			return ((t_new_pos){0, 1});
		if (num == 1)
			return ((t_new_pos){-1, 0});
	}
	else if (num == 2 || num == 3)
	{
		*pos = 1;
		if (num == 2)
			return ((t_new_pos){0, -1});
		if (num == 3)
			return ((t_new_pos){1, 0});
	}
	return ((t_new_pos){0, 0});
}
