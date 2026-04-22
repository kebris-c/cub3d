/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:16:22 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/22 00:00:00 by kebris-c        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Map rules: charset, single spawn, outer ring is '1'. Interior flood-fill
** for full closure is left to the student (TODO).
*/
int	is_map_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == ' '
				|| line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'))
			return (0);
		i++;
	}
	return (1);
}

static int	register_spawn(t_config *cfg, int x, int y, int *found)
{
	char	c;

	c = cfg->map.grid[y][x];
	if (!(c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return (EXIT_SUCCESS);
	if (*found)
		return (error_msg("multiple spawns detected"));
	cfg->player_x = x + 0.5;
	cfg->player_y = y + 0.5;
	cfg->player_dir = c;
	cfg->map.grid[y][x] = '0';
	*found = 1;
	return (EXIT_SUCCESS);
}

static int	find_single_spawn(t_config *cfg)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			if (register_spawn(cfg, x, y, &found) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	if (!found)
		return (error_msg("missing player spawn"));
	return (EXIT_SUCCESS);
}

static int	map_border_is_walled(t_config *cfg)
{
	int	x;
	int	y;

	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			if (y == 0 || y == cfg->map.height - 1
				|| x == 0 || x == cfg->map.width - 1)
			{
				if (cfg->map.grid[y][x] != '1')
					return (error_msg("map border must be walls"));
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	validate_map(t_config *cfg)
{
	if (cfg->map.height <= 0 || cfg->map.width <= 0 || !cfg->map.grid)
		return (error_msg("empty map"));
	if (find_single_spawn(cfg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (map_border_is_walled(cfg));
}
