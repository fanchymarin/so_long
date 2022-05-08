/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:09:25 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/08 15:32:26 by fmarin-p         ###   ########.fr       */
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
