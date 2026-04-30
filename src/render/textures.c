/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:21:26 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 14:36:09 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_wall_hit(t_ray *ray, t_image *img)
{
	double	wall_x;
	double	text_x;

	if (ray->side == 0)
		wall_x = ray->player_y + ray->perp_dist_wall * ray->dir_y;
	else
		wall_x = ray->player_x + ray->perp_dist_wall * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	text_x = wall_x * img->width;
	return (text_x);
}

void	render_loop_calculations(t_ray *ray, t_game *game, t_cal *cal)
{
	t_image	*tex;
	double	offset;

	tex = &game->textures[ray->dir_id];
	cal->step = 0;
	cal->text_x = 0;
	cal->text_y = 0;
	cal->step = (double)tex->height / (double)ray->line_height;
	cal->text_x = calculate_wall_hit(ray, tex);
	offset = (ray->draw_start - ((WIN_HEIGHT / 2) - (ray->line_height / 2)));
	cal->text_y = offset * cal->step;
}
