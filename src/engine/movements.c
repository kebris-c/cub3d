/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:38:46 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/09 18:39:00 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	little_rotation(t_game *game, double angle)
{
	double	old_x;
	double	old_y;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		old_x = game->rays[x].dir_x;
		old_y = game->rays[x].dir_y;
		game->rays[x].dir_x = old_x * cos(angle) - old_y * sin(angle);
		game->rays[x].dir_y = old_y * sin(angle) + old_x * cos(angle);
		x++;
	}
}
