/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:18:47 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/12 20:04:15 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Function to calculate the distance a vector `x` can advance
 * in `(x, y)` before the colision with other `(x, y)` square in the
 * the `map->grid`, with the Theorem of Pythagoras.
 * 
 * @param game Pointer to the game structure `t_game`, that contains
 * 				the array of rays `t_rays`.
 * @param x	Integer that determine the vector `x` from the player position.
 * 
 * @note The division between an integer and 0 is protected. The result will be
 * 		`1e30` in C (infinite). This case ocurrs when the player is facing in
 * 		a direction where the vector never hits an `x` or `y` side of a square in
 * 		the grid.
 */
static void	pythagoras_tan(t_game *game, int *x)
{
	if (fabs(game->rays[*x].dir_x) < 1e-6)
		game->rays[*x].delta_dist_x = 1e30;
	else
		game->rays[*x].delta_dist_x = fabs(1 / game->rays[*x].dir_x);
	if (fabs(game->rays[*x].dir_y) < 1e-6)
		game->rays[*x].delta_dist_y = 1e30;
	else
		game->rays[*x].delta_dist_y = fabs(1 / game->rays[*x].dir_y);
}

/**
 * @brief Function that calculates the distance a vector `x` will have
 * in `(x, y)` from the player, located in a `(x, y)` square in the
 * the `map->grid`.
 * 
 * This determines if the direction of a vector `x` is left (minor than 0)
 * or right (greater than 0). This includes both `(x, y)`.
 * 
 * @param game Pointer to the game structure `t_game`, that contains
 * 				the array of rays `t_rays`.
 * @param x	Integer that determine the vector `x` from the player position.
 * 
 * @note This function must be used at the beginning of the calculations.
 * The vectors are normalized, as well as proportionalized. So the `distance`
 * moving forward will be the same in both axis. The only interrumption will
 * ocurr when in the loop, the `map_x` and `map_y` are != 0 (a wall).
 */
static void	proyect_vector(t_game *game, int *x)
{
	if (game->rays[*x].dir_x < 0)
	{
		game->rays[*x].step_x = -1;
		game->rays[*x].side_dist_x = (game->player.x - game->rays[*x].map_x)
			* game->rays[*x].delta_dist_x;
	}
	else
	{
		game->rays[*x].step_x = 1;
		game->rays[*x].side_dist_x = (game->rays[*x].map_x + 1.0
				- game->player.x) * game->rays[*x].delta_dist_x;
	}
	if (game->rays[*x].dir_y < 0)
	{
		game->rays[*x].step_y = -1;
		game->rays[*x].side_dist_y = (game->player.y
				- game->rays[*x].map_y) * game->rays[*x].delta_dist_y;
	}
	else
	{
		game->rays[*x].step_y = 1;
		game->rays[*x].side_dist_y = (game->rays[*x].map_y + 1.0
				- game->player.y) * game->rays[*x].delta_dist_y;
	}
}

/**
 * @brief Function that cast every single ray from the player perspective.
 * 
 * With the reason `y = 2x - 1`, which determines that the `y` is the
 * wide size of the player FOV, this function calculates the `dir_x`
 * and `dir_y` of a `x` ray. It also gives each ray, the position
 * of the player in the `grid` (map).
 * 
 * @param game	Pointer to the game structure `t_game`, that contains
 * 			the array of rays `t_rays`.
 * @param cam_factor  Wide size of the FOV of the player.
 * @note the cam_factor cannot be 0, or a allocated space in memory!!
 */
static void	cast_rays(t_game *game, double cam_factor[WIN_WIDTH])
{
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		game->rays[x].dir_x = game->player.dir_x
			+ game->player.plane_x * cam_factor[x];
		game->rays[x].dir_y = game->player.dir_y
			+ game->player.plane_y * cam_factor[x];
		game->rays[x].map_x = (int)game->player.x;
		game->rays[x].map_y = (int)game->player.y;
		x++;
	}
}

/**
 * @brief Function that begins the raycasting.
 * 
 * This determines the perspective betweem the player and the walls. This does
 * not include objects, doors, enemies or any other objects in the game.
 * 
 * @param game Pointer to the game structure `t_game`, that contains
 * 				the array of rays `t_rays`.
 * @param map Pointer to the information of the map.
 * @param x	Integer that determine the vector `x` from the player position.
 */
void	look_for_walls(t_game *game, t_map *map, int *x)
{
	double	cam_factor[WIN_WIDTH];
	int		hit;

	hit = 0;
	cast_rays(game, cam_factor);
	pythagoras_tan(game, x);
	proyect_vector(game, x);
	while (hit == 0)
	{
		if (game->rays[*x].side_dist_x < game->rays[*x].side_dist_y)
		{
			game->rays[*x].side_dist_x += game->rays[*x].delta_dist_x;
			game->rays[*x].map_x += game->rays[*x].step_x;
			game->rays[*x].side = 0;
		}
		else
		{
			game->rays[*x].side_dist_y += game->rays[*x].delta_dist_y;
			game->rays[*x].map_y += game->rays[*x].step_y;
			game->rays[*x].side = 1;
		}
		if (map.grid[game->rays[*x].map_y][game->rays[*x].map_x] == '1')
			hit = 1;
	}
}
