/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:21:26 by kjroydev          #+#    #+#             */
/*   Updated: 2026/05/01 17:18:53 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_wall_hit(t_ray *ray, t_image *img)
{
	double	wall_x;
	double	tex_x;
	int		flip;

	flip = 0;
	if (ray->side == 0)
		wall_x = ray->player_y + ray->perp_dist_wall * ray->dir_y;
	else
		wall_x = ray->player_x + ray->perp_dist_wall * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_x = wall_x * img->width;
	if ((ray->side == 0 && ray->dir_x > 0) ||
		(ray->side == 1 && ray->dir_y < 0))
		tex_x = img->width - tex_x - 1;
	return (tex_x);
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
