/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:46:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/02 14:55:46 by fmarin-p         ###   ########.fr       */
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
