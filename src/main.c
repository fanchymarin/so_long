/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:43:25 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/08 16:31:52 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_handling(int error)
{
	if (!error)
		printf("Usage: ./so_long [.ber file]\n");
	else if (error == 1)
		perror("Error opening/reading file");
	else if (error == 2)
		perror("Error using malloc");
	else if (error == 3)
		printf("File not valid. Extension .ber required.\n");
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

	if (argc != 2)
		error_handling(0);
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		error_handling(3);
	map = read_map(argv[1]);
	check_map(map);
	return (0);
}
