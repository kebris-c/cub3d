/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c        #+#    #+#               */
/*   Updated: 2026/04/20 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
			put_pixel(&game->frame, x++, y, game->cfg.ceil_color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			put_pixel(&game->frame, x++, y, game->cfg.floor_color);
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
