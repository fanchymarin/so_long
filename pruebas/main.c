/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:02:33 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/12 17:19:35 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#define PIXEL_SIZE 125
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;

}				t_data;


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, PIXEL_SIZE * 5, 600, "Hello world!");
	img.img = mlx_xpm_file_to_image(mlx, "../sprites/0.xpm", &img.width, &img.height);
	int	x = 0;
	int	i = 5;
	while (i--)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, x, 0);
		x += PIXEL_SIZE;
		}
	mlx_loop(mlx);
}
