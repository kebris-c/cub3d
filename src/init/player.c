/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:37:51 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/09 18:38:02 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_game *game)
{
	game->player.x = game->cfg.player_x;
	game->player.y = game->cfg.player_y;
	game->player.dir_x = 1.0; //chage for N, S, W, E for player sight direction
	game->player.dir_y = 0.0; //chage for N, S, W, E for player sight direction
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
}
