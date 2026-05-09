/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/21 13:50:24 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Program entry: validate CLI, heap-allocate t_game (large ray buffers),
** parse .cub, init MLX, register hooks, run the main loop, then teardown.
*/
static void	free_game_heap_block(t_game *game)
{
	if (!game)
		return ;
	free(game);
}

/* Loads scene file and graphics; returns EXIT_FAILURE on parse or MLX init. */
static int	load_scene_and_init_mlx(t_game *game, const char *cub_path)
{
	game->cfg.floor_color = -1;
	game->cfg.ceil_color = -1;
	if (parse_cub_file(&game->cfg, cub_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_game(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Wires keyboard, window close, and per-frame callback into miniLibX. */
static void	register_mlx_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (error_msg("usage: ./cub3D path/to/scene.cub"));
	if (!file_has_extension(argv[1], ".cub"))
		return (error_msg("map file must use .cub extension"));
	game = ft_calloc(1, sizeof(*game));
	if (!game)
		return (error_msg("malloc failed"));
	if (load_scene_and_init_mlx(game, argv[1]) == EXIT_FAILURE)
		return (cleanup_game(game), free_game_heap_block(game), EXIT_FAILURE);
	register_mlx_hooks(game);
	signals_install();
	mlx_loop(game->mlx);
	signals_restore();
	cleanup_game(game);
	free_game_heap_block(game);
	return (EXIT_SUCCESS);
}
