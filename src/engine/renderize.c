/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 17:57:37 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/17 21:43:22 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/** 
 * @brief 
 */
static void	calculate_line_height(t_ray *ray, int x)
{
	int	draw_start;
	int	draw_end;
	int	h;

	h = WIN_HEIGHT;
	ray->line_height[x] = (int)(h / ray->perp_dist_wall);
	draw_start = (-ray->line_height[x] / 2) + (h / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (ray->line_height[x] / 2) + (h / 2);
	if (draw_end >= h)
		draw_end = h - 1;
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
		calculate_line_height(ray, game, x);
		x++;
	}
}

/*
* TODO (renderer): Implement DDA raycasting and textured wall slices.
* This skeleton only paints ceiling/floor bands as a placeholder.
*/
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
