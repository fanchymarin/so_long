/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:43:25 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/21 12:29:34 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_handling(int error)
{
	printf("Error\n");
	if (!error)
		printf("Correct usage: ./so_long [.ber file]\n");
	else if (error == 1)
		perror("Open/read of file");
	else if (error == 2)
		perror("Use of malloc");
	else if (error == 3)
		printf("File not valid. Extension .ber required.\n");
	else if (error == 4)
		printf("Minilibx failed.\n");
	exit(1);
}

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
		printf("Map needs to be rectangular\n");
	exit(1);
}

char	*read_map(char *file)
{
	int		fd;
	int		bytes_read;
	char	*buf;
	char	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handling(1);
	map = (char *) ft_calloc(sizeof(char), 1);
	buf = (char *) ft_calloc(sizeof(char), 100);
	if (!map || !buf)
		error_handling(2);
	while (1)
	{
		bytes_read = read(fd, buf, 100);
		if (bytes_read == -1)
			error_handling(1);
		if (!bytes_read)
			break ;
		map = concat_str(map, buf);
	}
	free(buf);
	close(fd);
	return (map);
}

int	main(int argc, char **argv)
{
	char	*map;
	t_mlx	mlx;

	if (argc != 2)
		error_handling(0);
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		error_handling(3);
	map = read_map(argv[1]);
	mlx.line = ft_split(map, '\n');
	mlx.stats = check_map(map, mlx.line);
	mlx_use(mlx.line, &mlx);
	free_dp(mlx.line);
	return (0);
}
