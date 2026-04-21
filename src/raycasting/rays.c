/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:18:47 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/20 20:25:24 by kjroydev         ###   ########.fr       */
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
static void	calculate_delta_dist(t_ray *ray)
{
	if (fabs(ray->dir_x) < 1e-6)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (fabs(ray->dir_y) < 1e-6)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
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
 * The vectors are proportionalized. So the `distance`
 * moving forward will be the same in both axis. The only interrumption will
 * ocurr when in the loop, the `map_x` and `map_y` are != 0 (a wall).
 */
static void	proyect_vector(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->player_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0
				- ray->player_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->player_y
				- ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0
				- ray->player_y) * ray->delta_dist_y;
	}
}

/**
 * @brief Function that begins the raycasting.
 * 
 * This determines the perspective betweem the player and the walls. This does
 * not include objects, doors, enemies or any other objects in the game.
 * 
 * @param ray Pointer to the structure `t_ray`, that contains
 * 				the array of rays.
 * @param map Pointer to the information of the map.
 * @param cam_factor  Wide size of the FOV of the player.
 * @param i	Integer that represents a iterator. This controls the loop
 * and prevents infinte proyection.
 * @note `i` must be 0 at the start of each loop.
 */
static t_hit_state	look_for_walls(t_ray *ray, t_map *map, int i)
{
	t_hit_state	state;

	state = HIT_NONE;
	while (state == HIT_NONE && i < MAX_STEPS)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= map->height
			|| ray->map_x < 0 || ray->map_x >= map->width)
			state = HIT_OOB;
		else if (map->grid[ray->map_y][ray->map_x] == '1')
			state = HIT_WALL;
		i++;
	}
	return (state);
}

/**
 * @brief Function that cast every single ray from the player perspective.
 * 
 * With the reason `y = 2x - 1`, which determines that the `y` is the
 * wide size of the player FOV, this function calculates the `dir_x`
 * and `dir_y` of a `x` ray. It also gives each ray, the position
 * of the player in the `grid` (map).
 * 
 * @param game	Pointer to the game structure `t_game`.
 * @param ray Pointer to the structure `t_ray`, that contains
 * 				the array of rays.
 * @param cam_factor  Wide size of the FOV of the player.
 * @note the cam_factor cannot be 0, or a allocated space in memory!!
 */
void	cast_rays(t_game *game, t_ray *ray, double cam_factor)
{
	ray->dir_x = game->player.dir_x + game->player.plane_x * cam_factor;
	ray->dir_y = game->player.dir_y + game->player.plane_y * cam_factor;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
}

/**
 * @brief Function that contains every step of the raycasting loop.
 * 
 * This function contains al the necesary steps in order to calculate
 * the distance between the player and every wall in the `map->grid`.
 * This also includes the correction of the fish eye effect, when the
 * player travels in the world
 * 
 * @param ray Pointer to the structure `t_ray`, that contains
 * 				the array of rays.
 * @param map Pointer to the information of the map.
 */
int	dda_loop(t_ray *ray, t_map *map, int x)
{
	t_hit_state	state;

	calculate_delta_dist(ray);
	proyect_vector(ray);
	state = look_for_walls(ray, map, 0);
	if (state == HIT_WALL)
	{
		if (ray->side == 0)
			ray->perp_dist_wall[x] = ray->side_dist_x
				- ray->delta_dist_x;
		else
			ray->perp_dist_wall[x] = ray->side_dist_y
				- ray->delta_dist_y;
	}
	else
		ray->perp_dist_wall[x] = 1e30;
	return (0);
}
