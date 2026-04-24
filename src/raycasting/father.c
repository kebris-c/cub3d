/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:29:17 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/24 11:32:47 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/** 
 * @brief Function that calculates the height of the walls.
 * 
 * This Function creates the Z-Buffer that will contain the height
 * and `perp_dist_wall` for each vector `x` from the player. This renderize
 * the wall at the correct perspective from the player, based
 * in the inverse of `perp_dist_wall`, calculating the leg of a triangule.
 * 
 * @param ray `t_ray` struct containing the information of vector `x`.
 * 
 * @param z_buffer array with `n` vectors lenght, that stores every ray
 * perpendicular distance ()
 */
static void	calculate_line_height(t_ray *ray, double *z_buffer)
{
	int	h;

	h = WIN_HEIGHT;
	*z_buffer = ray->perp_dist_wall;
	ray->line_height = (int)(h / ray->perp_dist_wall);
	ray->draw_start = (-ray->line_height / 2) + (h / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (h / 2);
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
}

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
