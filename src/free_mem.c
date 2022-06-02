/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:23:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/06/02 13:26:39 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->images.f1);
	mlx_destroy_image(mlx->mlx, mlx->images.f2);
	mlx_destroy_image(mlx->mlx, mlx->images.f3);
	mlx_destroy_image(mlx->mlx, mlx->images.r1);
	mlx_destroy_image(mlx->mlx, mlx->images.r2);
	mlx_destroy_image(mlx->mlx, mlx->images.r3);
	mlx_destroy_image(mlx->mlx, mlx->images.dl_c);
	mlx_destroy_image(mlx->mlx, mlx->images.dr_c);
	mlx_destroy_image(mlx->mlx, mlx->images.ul_c);
	mlx_destroy_image(mlx->mlx, mlx->images.ur_c);
	mlx_destroy_image(mlx->mlx, mlx->images.d_w);
	mlx_destroy_image(mlx->mlx, mlx->images.l_w);
	mlx_destroy_image(mlx->mlx, mlx->images.r_w);
	mlx_destroy_image(mlx->mlx, mlx->images.u_w);
}

void	destroy_sprites(t_mlx *mlx, t_list **sprite)
{
	t_list	*tmp;

	while (*sprite)
	{
		tmp = (*sprite)->next;
		mlx_destroy_image(mlx->mlx, (*sprite)->content);
		free(*sprite);
		*sprite = tmp;
	}
	free(sprite);
}

void	free_mem(void)
{
	int	i;

	i = 0;
	destroy_images(mlx);
	destroy_sprites(mlx, mlx->collect);
	destroy_sprites(mlx, mlx->exit);
	free_dp(mlx->line);
	free_dp(mlx->f_pos);
	free(mlx->c_pos);
	free(mlx->e_pos);
	free(mlx->p_pos);
	while (i < 4)
		destroy_sprites(mlx, mlx->player[i++]);
	free(mlx->player);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	free(mlx->mlx);
}
