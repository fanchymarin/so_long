/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:21:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/22 13:16:18 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	malloc_sprites(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->player = (t_list ***) malloc(sizeof(t_list **) * 4);
	while (i < 4)
	{
		mlx->player[i] = (t_list **) malloc(sizeof(t_list *));
		*mlx->player[i++] = 0;
	}
	mlx->collect = (t_list **) malloc(sizeof(t_list *));
	*mlx->collect = 0;
	mlx->exit = (t_list **) malloc(sizeof(t_list *));
	*mlx->exit = 0;
	mlx->c_pos = (struct s_pos *) ft_calloc(sizeof(struct s_pos),
			mlx->stats.c);
	mlx->e_pos = (struct s_pos *) ft_calloc(sizeof(struct s_pos),
			mlx->stats.e);
	mlx->p_pos = (struct s_pos *) ft_calloc(sizeof(struct s_pos),
			mlx->stats.p);
}

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

void	mlx_load_sprites(t_mlx *mlx, t_list **collect, t_list **exit)
{
	int	a;
	int	b;

	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/c/c1.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/c/c2.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/c/c3.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/c/c2.xpm", &a, &b)));
	ft_lstadd_back(collect, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/c/c1.xpm", &a, &b)));
	ft_lstadd_back(exit, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/e/e.xpm", &a, &b)));
	ft_lstadd_back(exit, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/e/e1.xpm", &a, &b)));
	ft_lstadd_back(exit, ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
				"./assets/e/e2.xpm", &a, &b)));
}

void	mlx_load_player(t_mlx *mlx, t_list ***player)
{
	int		a;
	int		b;
	char	*p;
	char	*path;
	int		i;

	i = 0;
	p = "lur ";
	path = ft_strdup("./assets/p/d1.xpm");
	while (*p)
	{
		path[12] = '1';
		while (path[12] <= '3')
		{
			ft_lstadd_back(player[i], ft_lstnew(mlx_xpm_file_to_image(mlx->mlx,
						path, &a, &b)));
			path[12]++;
		}
		path[11] = *(p++);
		i++;
	}
	free(path);
}
