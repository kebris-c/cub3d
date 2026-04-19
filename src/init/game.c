/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:57:22 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/17 13:01:07 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("mlx_init failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (error_msg("mlx_new_window failed"));
	game->frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img)
		return (error_msg("mlx_new_image failed"));
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (error_msg("failed to read frame buffer"));
	if (set_default_colors_if_missing(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (load_textures_skeleton(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_player(game);
	return (EXIT_SUCCESS);
}
