/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:57:22 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/22 00:00:00 by kebris-c        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("mlx_init failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (error_msg("mlx_new_window failed"));
	return (EXIT_SUCCESS);
}

static int	init_frame_buffer(t_game *game)
{
	game->frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img)
		return (error_msg("mlx_new_image failed"));
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (error_msg("failed to read frame buffer"));
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	return (EXIT_SUCCESS);
}

static int	load_wall_texture_slot(t_game *game, int i)
{
	int	w;
	int	h;

	if (!game->cfg.tex_path[i] || !*game->cfg.tex_path[i])
		return (error_msg("missing wall texture path"));
	w = 0;
	h = 0;
	game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
			game->cfg.tex_path[i], &w, &h);
	if (!game->textures[i].img)
		return (error_msg("mlx_xpm_file_to_image failed"));
	game->textures[i].width = w;
	game->textures[i].height = h;
	game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
			&game->textures[i].bpp, &game->textures[i].line_len,
			&game->textures[i].endian);
	if (!game->textures[i].addr)
		return (error_msg("mlx_get_data_addr failed on texture"));
	return (EXIT_SUCCESS);
}

static int	load_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (load_wall_texture_slot(game, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_game(t_game *game)
{
	if (init_mlx_window(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_frame_buffer(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (load_wall_textures(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_player(game);
	return (EXIT_SUCCESS);
}
