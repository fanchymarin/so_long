/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:35 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/19 11:59:07 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_size(char **line, int which)
{
	int	size;

	size = 0;
	if (which)
	{
		while (line[size])
			++size;
	}
	else
	{
		while (line[0][size])
			++size;
	}
	return (size);
}

void	check_characters(char *map, t_map *stats)
{
	*stats = (t_map){.e = 0, .p = 0, .c = 0};
	while (*map)
	{
		if (*map != '1' && *map != '0' && *map != 'C'
			&& *map != 'E' && *map != 'P' && *map != '\n')
			map_error_handling(0);
		if (*map == 'E')
			stats->e++;
		else if (*map == 'C')
			stats->c++;
		else if (*map == 'P')
			stats->p++;
		++map;
	}
	if (!stats->p || !stats->c || !stats->e)
		map_error_handling(2);
}

void	check_rectangular(char **line, int width)
{
	int	i;
	int	i2;

	i = 1;
	while (line[i])
	{
		i2 = 0;
		while (line[i][i2])
			++i2;
		if (i2 != width)
			map_error_handling(3);
		i++;
	}
}

void	check_walls(char **line, int height, int width)
{
	int	i;

	i = 0;
	while (line[0][i] && line[height][i])
	{
		if (line[0][i] != '1' || line[height][i] != '1')
			map_error_handling(1);
		++i;
	}
	--height;
	while (height)
	{
		if (line[height][0] != '1' || line[height][width] != '1')
			map_error_handling(1);
		--height;
	}
}

t_map	check_map(char *map, char **line)
{
	t_map	stats;

	check_characters(map, &stats);
	stats.height = calculate_size(line, 1);
	stats.width = calculate_size(line, 0);
	check_rectangular(line, stats.width);
	check_walls(line, stats.height - 1, stats.width - 1);
	free(map);
	return (stats);
}
