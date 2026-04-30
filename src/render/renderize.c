/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 09:22:43 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 13:48:31 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	renderize_roof_floor(t_game *game)
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

void	render_frame(t_ray *ray, t_image *img, t_game *game)
{
	t_cal	cal;
	int		color;
	int		x;
	int		y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		render_loop_calculations(&ray[x], img, &cal);
		y = ray[x].draw_start;
		while (y < ray[x].draw_end)
		{
			color = get_texel(&game->textures[ray[x].dir_id], (int)cal.text_x, cal.text_y);
			if (ray[x].side == 0)
				put_pixel(&game->frame, x, y, color);
			else
				put_pixel(&game->frame, x, y, color);
			cal.text_y += cal.step;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
