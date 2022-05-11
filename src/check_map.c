/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:35 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/11 13:39:57 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error_handling(int error)
{
	printf("Error\n");
	if (!error)
		printf("Invalid characters in file.\n");
	else if (error == 1)
		printf("Walls (1) not closing the map.\n");
	else if (error == 2)
		printf("Needed at least one of each characters: (E), (C), (P).\n");
	else if (error == 3)
		printf("Only one initial position (P) allowed.\n");
	else if (error == 4)
		printf("Map needs to be rectangular\n");
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
	t_check	check;

	check = (t_check){0, 0, 0};
	while (*map)
	{
		if (*map != '1' && *map != '0' && *map != 'C'
			&& *map != 'E' && *map != 'P' && *map != '\n')
			map_error_handling(0);
		if (*map == 'E')
			check.e++;
		else if (*map == 'C')
			check.c++;
		else if (*map == 'P')
			check.p++;
		++map;
	}
	if (!check.p || !check.c || !check.e)
		map_error_handling(2);
	if (check.p > 1)
		map_error_handling(3);
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

char	**check_map(char *map)
{
	char	**line;
	int		height;
	int		width;

	check_characters(map);
	line = ft_split(map, '\n');
	height = calculate_size(line, 1);
	width = calculate_size(line, 0);
	if (height > width)
		map_error_handling(4);
	check_walls(line, height - 1, width - 1);
	free(map);
	return (line);
}
