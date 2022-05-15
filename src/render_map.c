/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:35:49 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/15 20:43:58 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_load_images(t_mlx *mlx)
{
	int		a;
	int		b;
	void	*p;
	char	*path;

	path = "./assets/floor/grass1.xpm";
	mlx->images.f1 = mlx_xpm_file_to_image(mlx->mlx, path, &a, &b);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.f1, 0, 0);
	p = mlx.images.f1;
	printf("%u, %u, %u\n", p, mlx->images.f1, mlx->images.f2)
}

void	mlx_use(char **line, t_map stats)
{
	t_mlx	mlx;
	(void)	line;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, PSIZE * stats.width, 
								PSIZE * stats.height, "so_long");
	if (!mlx.mlx || !mlx.mlx_win)
		error_handling(4);
	mlx_load_images(&mlx);
	mlx_loop(mlx.mlx);
}
