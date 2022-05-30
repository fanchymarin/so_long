/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:07:51 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/05/30 12:09:20 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	last_dir(int key)
{
	if (key == KEY_S)
		return (0);
	else if (key == KEY_A)
		return (1);
	else if (key == KEY_W)
		return (2);
	else if (key == KEY_D)
		return (3);
	return (0);
}
