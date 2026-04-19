/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c        #+#    #+#               */
/*   Updated: 2026/04/20 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Teardown: free parsed paths/map, destroy MLX images/window/display safely
** when pointers exist (parse failures may stop before MLX is ready).
*/
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

static void	destroy_visual_resources(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->mlx && game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		game->textures[i].img = NULL;
		i++;
	}
	if (game->mlx && game->frame.img)
	{
		mlx_destroy_image(game->mlx, game->frame.img);
		game->frame.img = NULL;
	}
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
}

static void	destroy_mlx_instance(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	destroy_visual_resources(game);
	destroy_mlx_instance(game);
	free_config(&game->cfg);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
