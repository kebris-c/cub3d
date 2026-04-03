#include "cub3d.h"

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

static void	move_forward_backward(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * speed;
	new_y = game->player.y + game->player.dir_y * speed;
	if (is_walkable(&game->cfg.map, new_x, game->player.y))
		game->player.x = new_x;
	if (is_walkable(&game->cfg.map, game->player.x, new_y))
		game->player.y = new_y;
}

static void	move_strafe(t_game *game, double speed)
{
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	perp_x = -game->player.dir_y;
	perp_y = game->player.dir_x;
	new_x = game->player.x + perp_x * speed;
	new_y = game->player.y + perp_y * speed;
	if (is_walkable(&game->cfg.map, new_x, game->player.y))
		game->player.x = new_x;
	if (is_walkable(&game->cfg.map, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_player(t_game *game)
{
	/*
	** Skeleton movement:
	** Keep keyboard plumbing in place, but leave real movement/collision tuning
	** to your implementation pass.
	*/
	if (game->keys.w || game->keys.s || game->keys.a || game->keys.d
		|| game->keys.left || game->keys.right)
	{
		if (game->keys.w)
			move_forward_backward(game, MOVE_SPEED);
		if (game->keys.s)
			move_forward_backward(game, -MOVE_SPEED);
		if (game->keys.a)
			move_strafe(game, -MOVE_SPEED);
		if (game->keys.d)
			move_strafe(game, MOVE_SPEED);
		if (game->keys.left)
			rotate_player(game, -ROT_SPEED);
		if (game->keys.right)
			rotate_player(game, ROT_SPEED);
	}
}
