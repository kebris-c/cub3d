/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 17:57:37 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/20 21:19:45 by kjroydev         ###   ########.fr       */
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
 * @param ray `t_ray` struct containing the information of vector `x`
 * @param x integer that represent to identify a vector in the array
 * of vectors.
 */
static void	calculate_line_height(t_ray *ray, t_render *render, int x)
{
	int	draw_start;
	int	draw_end;
	int	h;

	h = WIN_HEIGHT;
	render->z_buffer[x] = ray->perp_dist_wall[x];
	ray->line_height[x] = (int)(h / ray->perp_dist_wall[x]);
	ray->draw_start[x] = (-ray->line_height[x] / 2) + (h / 2);
	if (ray->draw_start[x] < 0)
		ray->draw_start[x] = 0;
	ray->draw_end[x] = (ray->perp_dist_wall[x] / 2) + (h / 2);
	if (ray->draw_end[x] >= h)
		ray->draw_end[x] = h - 1;
}

void	renderize_roof_floor(t_image *frame)
{
	int	win_middle;
	int	x;
	int	y;

	y = 0;
	win_middle = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < win_middle)
				put_pixel(frame, x, y, SKY_COLOR);
			else
				put_pixel(frame, x, y, FLOOR_COLOR);
			x++;
		}
		y++;
	}
}

void	render_frame(t_ray *ray, t_image *img, int x)
{
	int	x;
	int	y;

	x = 0;
	y = ray->draw_start[x];
	while (y < ray->draw_end[x])
	{
		if (ray->side == 0)
			put_pixel(img, x, y, 0x00FF00);
		else
			put_pixel(img, x, y, 0xFF0000);
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

void	map_raycasting(t_game *game, t_map *map)
{
	double	cam_factor[WIN_WIDTH];
	t_ray	*ray;
	int		x;

	x = 0;
	precal_camera_factors(cam_factor);
	while (x < WIN_WIDTH)
	{
		ray = &game->ray[x];
		cast_rays(game, ray, cam_factor[x]);
		dda_loop(ray, map, x);
		calculate_line_height(ray, &game->render, x);
		render_frame(ray, &game->render, x);
		x++;
	}
}
