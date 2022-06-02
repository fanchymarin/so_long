/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:22:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/02 16:02:59 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_s(t_mlx *mlx, void **sprite, t_pos *pos)
{
	int			i;
	static int	mov = 0;

	i = 0;
	while (i < mlx->stats.s)
	{
		print(mlx, 0, pos->x, pos->y);
		print(mlx, sprite[mov], pos->x, pos->y);
		++i;
	}
	if (++mov == 4)
		mov = 0;
}

void	slime_ai(t_mlx *mlx)
{
	static int	i = 0;

	animate_s(mlx, mlx->slime[i], mlx->s_pos);
}
