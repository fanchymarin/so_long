/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:43:25 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/11 15:22:52 by fmarin-p         ###   ########.fr       */
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

void	mlx_use(char **line)
{
	void	*mlx;
	void	*win_mlx;

	(void) line;
	mlx = mlx_init();
	win_mlx = mlx_new_window(mlx, 1024, 768, "so_long");
	if (!mlx || !win_mlx)
		error_handling(4);
	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	char	*map;
	char	**line;

	if (argc != 2)
		error_handling(0);
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		error_handling(3);
	map = read_map(argv[1]);
	line = check_map(map);
	mlx_use(line);
	free_dp(line);
	//system("leaks so_long");
	return (0);
}
