/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/21 13:52:55 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	else if (keycode == XK_w)
		game->keys.w = 1;
	else if (keycode == XK_s)
		game->keys.s = 1;
	else if (keycode == XK_a)
		game->keys.a = 1;
	else if (keycode == XK_d)
		game->keys.d = 1;
	else if (keycode == XK_Left)
		game->keys.left = 1;
	else if (keycode == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 0;
	else if (keycode == XK_s)
		game->keys.s = 0;
	else if (keycode == XK_a)
		game->keys.a = 0;
	else if (keycode == XK_d)
		game->keys.d = 0;
	else if (keycode == XK_Left)
		game->keys.left = 0;
	else if (keycode == XK_Right)
		game->keys.right = 0;
	return (0);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (cub_signal_stop_requested())
	{
		mlx_loop_end(game->mlx);
		return (0);
	}
	renderize_roof_floor(game);
	move_player(game);
	map_raycasting(game, &game->cfg.map);
	render_frame(game->ray, &game->frame, game);
	return (0);
}
