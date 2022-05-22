/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:14:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/22 20:09:39 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ret_f(t_mlx *mlx, int x, int y)
{
	if (mlx->f_pos[y][x] == 1)
		return (mlx->images.f1);
	else if (mlx->f_pos[y][x] == 2)
		return (mlx->images.f2);
	else
		return (mlx->images.f3);
}


int	animate_sprites(t_mlx *mlx)
{
	animate_c(mlx);
	animate_e(mlx);
	return (0);
}
