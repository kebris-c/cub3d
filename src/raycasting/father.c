/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:29:17 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 15:28:52 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_raycasting(t_game *game, t_map *map)
{
	double		cam_factor[WIN_WIDTH];
	t_ray		*ray;
	int			x;

	x = 0;
	precal_camera_factors(cam_factor);
	while (x < WIN_WIDTH)
	{
		ray = &game->ray[x];
		cast_rays(&game->player, ray, cam_factor[x]);
		dda_loop(ray, map);
		calculate_line_height(ray, &game->render.z_buffer[x]);
		get_direction(ray);
		x++;
	}
}
