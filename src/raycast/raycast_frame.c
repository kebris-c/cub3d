/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:29:17 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 15:28:52 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_raycast_for_entire_frame(t_game *game, t_map *map)
{
	double		cam_factor[WIN_WIDTH];
	t_ray		*ray;
	int			x;

	x = 0;
	init_screen_column_camera_factors(cam_factor);
	while (x < WIN_WIDTH)
	{
		ray = &game->ray[x];
		ray_init_column_dir_from_player(&game->player, ray, cam_factor[x]);
		ray_run_dda(ray, map);
		ray_compute_wall_strip_vertical_span(ray, &game->render.z_buffer[x]);
		ray_assign_wall_texture_by_hit_side(ray);
		x++;
	}
}
