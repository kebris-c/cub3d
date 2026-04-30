/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:21:26 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 08:43:24 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

double	calculate_pixel_hit(t_ray *ray, t_image img)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->player_y + ray->perp_dist_wall * ray->dir_y;
	else
		wall_x = ray->player_x + ray->perp_dist_wall * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	ray->text_x = wall_x * img.width;
}

static int	load_textures_skeleton(t_game *game)
{
	(void)game;
	return (EXIT_SUCCESS);
}
