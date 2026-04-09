/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:18:47 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/09 20:40:17 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	precal_camera_factors(double cam_factor[WIN_WIDTH])
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cam_factor[x] = 2.0 * x / (double)(WIN_WIDTH - 1) - 1.0;
		x++;
	}
}

static void	create_rays(t_game *game, double cam_factor[WIN_WIDTH])
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		game->rays[x].dir_x = game->player.dir_x
			+ game->player.plane_x * cam_factor[x];
		game->rays[x].dir_y = game->player.dir_y
			+ game->player.plane_y * cam_factor[x];
		game->rays[x].map_x = (int)game->player.x;
		game->rays[x].map_y = (int)game->player.y;
		x++;
	}
}

void	hit_calculations(t_game *game)
{
	double	delta_dist_x; //distance to the next x-side
	double	delta_dist_y; //distance to the next y-side
	double	side_dist_x; //initial distance the ray travel for the first x-plane
	double	side_dist_y; //initial distance the ray travel for the first y-plane
	int		x;

	x = 0;
	delta_dist_x = fabs(1 / game->rays[x].dir_x);
	delta_dist_y = fabs(1 / game->rays[x].dir_y);
}

void	render_frame(t_game *game)
{
	int	x;
	int	y;

	/*
	** TODO (renderer): Implement DDA raycasting and textured wall slices.
	** This skeleton only paints ceiling/floor bands as a placeholder.
	*/
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
