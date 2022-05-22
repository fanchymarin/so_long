/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:09:25 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/22 19:10:32 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*concat_str(char *memory, char *buf)
{
	char	*concat;

	concat = ft_strjoin(memory, buf);
	free(memory);
	ft_bzero(buf, 100);
	return (concat);
}

void	free_dp(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

int	ft_rand(void)
{
	static unsigned long int	next = 1;

	next = next * 1103515245 + 12345;
	return ((unsigned int)(next / 65536) % 32768);
}

void	save_pos(struct s_pos *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
}

void	store_f_pos(t_mlx *mlx, int x, int y, int id)
{
	int	i;

	if (!mlx->f_pos)
	{
		i = 0;
		mlx->f_pos = (char **) ft_calloc(sizeof(char *),
				(mlx->stats.height + 1));
		while (i < mlx->stats.height)
			mlx->f_pos[i++] = (char *) ft_calloc(sizeof(char),
					(mlx->stats.width + 1));
	}
	if (id == 1)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->images.f1, x * PSIZE, y * PSIZE);
	else if (id == 2)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->images.f2, x * PSIZE, y * PSIZE);
	else if (id == 3)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->images.f3, x * PSIZE, y * PSIZE);
	mlx->f_pos[y][x] = id;
}
