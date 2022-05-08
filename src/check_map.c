/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:35 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/08 16:42:35 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error_handling(int error)
{
	printf("[MAP ERROR]: ");
	if (!error)
		printf("Invalid characters in file.\n");
	else if (error == 1)
		printf("Walls not closed.\n");
	exit(1);
}

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

void	check_characters(char *map)
{
	while (*map)
	{
		if (*map != '1' && *map != '0' && *map != 'C'
			&& *map != 'E' && *map != 'P' && *map != '\n')
			map_error_handling(0);
		++map;
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
	while (height > 1)
	{
		if (line[height][0] != '1' || line[height][width] != '1')
			map_error_handling(1);
		--height;
	}
}

void	check_map(char *map)
{
	char	**line;
	int		height;
	int		width;

	check_characters(map);
	line = ft_split(map, '\n');
	height = calculate_size(line, 1);
	width = calculate_size(line, 0);
	check_walls(line, height - 1, width - 1);
	free(map);
}
