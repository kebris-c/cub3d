/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 17:57:37 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/21 13:09:47 by kjroydev         ###   ########.fr       */
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
static void	calculate_line_height(t_ray *ray, double *z_buffer)
{
	int	h;

	h = WIN_HEIGHT;
	*z_buffer = ray->perp_dist_wall;
	ray->line_height = (int)(h / ray->perp_dist_wall);
	ray->draw_start = (-ray->line_height / 2) + (h / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->perp_dist_wall / 2) + (h / 2);
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
}

void	renderize_roof_floor(t_game *game)
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
				put_pixel(&game->frame, x, y, SKY_COLOR);
			else
				put_pixel(&game->frame, x, y, FLOOR_COLOR);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

void	render_frame(t_ray *ray, t_image *img, t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = ray[x].draw_start;
		while (y < ray[x].draw_end)
		{
			if (ray[x].side == 0)
				put_pixel(img, x, y, 0x00FF00);
			else
				put_pixel(img, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
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
		x++;
	}
}
