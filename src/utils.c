/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:09:25 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/20 18:14:41 by fmarin-p         ###   ########.fr       */
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
