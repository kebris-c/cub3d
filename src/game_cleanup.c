#include "cub3d.h"

void	free_config(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (cfg->tex_path[i])
			free(cfg->tex_path[i]);
		cfg->tex_path[i] = NULL;
		i++;
	}
	if (cfg->map.grid)
	{
		ft_free_matrix(cfg->map.grid);
		cfg->map.grid = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		game->textures[i].img = NULL;
		i++;
	}
	if (game->frame.img)
	{
		mlx_destroy_image(game->mlx, game->frame.img);
		game->frame.img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_config(&game->cfg);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
