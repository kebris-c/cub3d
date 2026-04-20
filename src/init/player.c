/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:37:51 by kjroydev        #+#    #+#               */
/*   Updated: 2026/04/20 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_facing_north(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = -1;
	pl->plane_x = 0.66;
	pl->plane_y = 0;
}

static void	set_facing_south(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = 1;
	pl->plane_x = -0.66;
	pl->plane_y = 0;
}

static void	set_facing_east(t_player *pl)
{
	pl->dir_x = 1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
}

static void	set_facing_west(t_player *pl)
{
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = -0.66;
}

void	init_player(t_game *game)
{
	game->player.x = game->cfg.player_x;
	game->player.y = game->cfg.player_y;
	if (game->cfg.player_dir == 'N')
		set_facing_north(&game->player);
	else if (game->cfg.player_dir == 'S')
		set_facing_south(&game->player);
	else if (game->cfg.player_dir == 'E')
		set_facing_east(&game->player);
	else if (game->cfg.player_dir == 'W')
		set_facing_west(&game->player);
	else
		set_facing_east(&game->player);
}
