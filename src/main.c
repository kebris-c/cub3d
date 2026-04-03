#include "cub3d.h"

/*
** TODO (engine): Replace this with subject-compliant camera setup and
** initialization taken from the parsed spawn (N/S/E/W).
*/
static void	init_player_skeleton(t_game *game)
{
	game->player.x = game->cfg.player_x;
	game->player.y = game->cfg.player_y;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
}

/*
** TODO (textures): Use mlx_xpm_file_to_image for NO/SO/WE/EA textures.
** This skeleton intentionally skips texture loading.
*/
static int	load_textures_skeleton(t_game *game)
{
	(void)game;
	return (EXIT_SUCCESS);
}

static int	set_default_colors_if_missing(t_game *game)
{
	if (game->cfg.floor_color == -1)
		game->cfg.floor_color = rgb_to_int(60, 60, 60);
	if (game->cfg.ceil_color == -1)
		game->cfg.ceil_color = rgb_to_int(120, 120, 180);
	game->player.x = game->cfg.player_x;
	return (EXIT_SUCCESS);
}

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
	init_player_skeleton(game);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg("usage: ./cub3D maps/example.cub"));
	if (!file_has_extension(argv[1], ".cub"))
		return (error_msg("map file must use .cub extension"));
	ft_bzero(&game, sizeof(game));
	game.cfg.floor_color = -1;
	game.cfg.ceil_color = -1;
	if (parse_cub_file(&game.cfg, argv[1]) == EXIT_FAILURE)
		return (cleanup_game(&game), EXIT_FAILURE);
	if (init_game(&game) == EXIT_FAILURE)
		return (cleanup_game(&game), EXIT_FAILURE);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
