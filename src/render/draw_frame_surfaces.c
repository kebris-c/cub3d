/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame_surfaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 09:22:43 by kjroydev          #+#    #+#             */
/*   Updated: 2026/05/01 15:06:39 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fullscreen_ceiling_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(&game->frame, x, y, game->cfg.ceil_color);
			else
				put_pixel(&game->frame, x, y, game->cfg.floor_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

void	draw_textured_wall_columns(t_ray *ray, t_game *game)
{
	t_wall_tex_column	texcol;
	int					color;
	int					x;
	int					y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		wall_strip_prepare_tex_coords(&ray[x], game, &texcol);
		y = ray[x].draw_start;
		while (y < ray[x].draw_end)
		{
			color = get_texel(&game->textures[ray[x].dir_id],
					(int)texcol.tex_column, (int)texcol.tex_row);
			if (ray[x].side == 0)
				put_pixel(&game->frame, x, y, color);
			else
				put_pixel(&game->frame, x, y, color);
			texcol.tex_row += texcol.row_step;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
