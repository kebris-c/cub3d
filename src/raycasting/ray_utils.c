/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:13:16 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 08:41:51 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	precal_camera_factors(double *cam_factor)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cam_factor[x] = 2.0 * x / (double)(WIN_WIDTH - 1) - 1.0;
		x++;
	}
}

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
void	calculate_line_height(t_ray *ray, double *z_buffer)
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
