/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:22:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/04 12:54:07 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_s(t_mlx *mlx, t_list **sprite, t_pos *pos)
{
	int			i;
	static int	speed = S_SPEED;

	i = 0;
	if (!pos->image)
		pos->image = *sprite;
	while (i < mlx->stats.s)
	{
		print(mlx, 0, pos[i].x, pos[i].y);
		print(mlx, pos->image->content, pos[i].x, pos[i].y);
		++i;
	}
	if (!speed--)
	{
		pos->image = pos->image->next;
		speed = S_SPEED;
	}
}

void	slime_ai(t_mlx *mlx)
{
	static int	i = 0;

	if (mlx->stats.s)
		animate_s(mlx, mlx->slime[i], mlx->s_pos);
}
