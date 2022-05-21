/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:34:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/21 13:12:28 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_c(t_mlx *mlx)
{
	static t_list	*collect = 0;
	int				i;

	usleep(60000);
	if (!collect)
		collect = (*mlx->collect);
	i = 0;
	while (i < mlx->stats.c)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			ret_f(mlx, mlx->c_pos[i].x, mlx->c_pos[i].y), mlx->c_pos[i].x
			* PSIZE, mlx->c_pos[i].y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			collect->content, mlx->c_pos[i].x * PSIZE, mlx->c_pos[i].y * PSIZE);
		i++;
	}
	collect = collect->next;
}

void	animate_e(t_mlx *mlx)
{
	static t_list	*exit = 0;
	int				i;

	usleep(60000);
	if (!exit)
		exit = (*mlx->exit);
	i = 0;
	while (i < mlx->stats.e)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			ret_f(mlx, mlx->e_pos[i].x, mlx->e_pos[i].y), mlx->e_pos[i].x
			* PSIZE, mlx->e_pos[i].y * PSIZE);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			exit->content, mlx->e_pos[i].x * PSIZE, mlx->e_pos[i].y * PSIZE);
		i++;
	}
	exit = exit->next;
}

int	animate_sprites(t_mlx *mlx)
{
	animate_c(mlx);
	animate_e(mlx);
	return (0);
}
