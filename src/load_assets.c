/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:21:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/19 15:21:49 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_load_images(void *mlx, struct s_images *images)
{
	int	a;
	int	b;

	images->f1 = mlx_xpm_file_to_image(mlx, "./assets/0/f1.xpm", &a, &b);
	images->f2 = mlx_xpm_file_to_image(mlx, "./assets/0/f2.xpm", &a, &b);
	images->f3 = mlx_xpm_file_to_image(mlx, "./assets/0/f3.xpm", &a, &b);
	images->r1 = mlx_xpm_file_to_image(mlx, "./assets/1-1/r1.xpm", &a, &b);
	images->r2 = mlx_xpm_file_to_image(mlx, "./assets/1-1/r2.xpm", &a, &b);
	images->r3 = mlx_xpm_file_to_image(mlx, "./assets/1-1/r3.xpm", &a, &b);
	images->dl_c = mlx_xpm_file_to_image(mlx, "./assets/1/dl_c.xpm", &a, &b);
	images->dr_c = mlx_xpm_file_to_image(mlx, "./assets/1/dr_c.xpm", &a, &b);
	images->ul_c = mlx_xpm_file_to_image(mlx, "./assets/1/ul_c.xpm", &a, &b);
	images->ur_c = mlx_xpm_file_to_image(mlx, "./assets/1/ur_c.xpm", &a, &b);
	images->d_w = mlx_xpm_file_to_image(mlx, "./assets/1/d_w.xpm", &a, &b);
	images->l_w = mlx_xpm_file_to_image(mlx, "./assets/1/l_w.xpm", &a, &b);
	images->r_w = mlx_xpm_file_to_image(mlx, "./assets/1/r_w.xpm", &a, &b);
	images->u_w = mlx_xpm_file_to_image(mlx, "./assets/1/u_w.xpm", &a, &b);
}

void	mlx_load_sprites(void *mlx, t_list **collect, t_list **exit)
{
	int	a;
	int	b;

	(void) exit;
	collect = (t_list **) malloc(sizeof(t_list *));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx,
					"./assets/c/c1.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx,
					"./assets/c/c2.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx,
					"./assets/c/c3.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx,
					"./assets/c/c2.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx,
					"./assets/c/c1.xpm", &a, &b)));
}
