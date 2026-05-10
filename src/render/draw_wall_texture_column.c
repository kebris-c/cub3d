/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_texture_column.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:21:26 by kjroydev          #+#    #+#             */
/*   Updated: 2026/05/01 17:18:53 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	compute_wall_texture_u(t_ray *ray, t_image *img)
{
	double	wall_x;
	double	tex_u;

	if (ray->side == 0)
		wall_x = ray->player_y + ray->perp_dist_wall * ray->dir_y;
	else
		wall_x = ray->player_x + ray->perp_dist_wall * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_u = wall_x * img->width;
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex_u = img->width - tex_u - 1;
	return (tex_u);
}

void	wall_strip_prepare_tex_coords(
			t_ray *ray,
			t_game *game,
			t_wall_tex_column *texcol)
{
	t_image	*tex;
	double	offset;

	tex = &game->textures[ray->dir_id];
	texcol->row_step = 0;
	texcol->tex_column = 0;
	texcol->tex_row = 0;
	texcol->row_step = (double)tex->height / (double)ray->line_height;
	texcol->tex_column = compute_wall_texture_u(ray, tex);
	offset = (ray->draw_start - ((WIN_HEIGHT / 2) - (ray->line_height / 2)));
	texcol->tex_row = offset * texcol->row_step;
}
