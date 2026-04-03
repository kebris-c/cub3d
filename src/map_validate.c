#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_line(const char *line)
{
	size_t	i;
	int		has_one;

	i = 0;
	has_one = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			has_one = 1;
		if (!(line[i] == '0' || line[i] == '1' || line[i] == ' '
				|| is_player_char(line[i])))
			return (0);
		i++;
	}
	return (has_one);
}

static int	find_single_spawn_skeleton(t_config *cfg)
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
			if (is_player_char(cfg->map.grid[y][x]))
			{
				if (found)
					return (error_msg("multiple spawns detected"));
				cfg->player_x = x + 0.5;
				cfg->player_y = y + 0.5;
				cfg->player_dir = cfg->map.grid[y][x];
				cfg->map.grid[y][x] = '0';
				found = 1;
			}
			x++;
		}
		y++;
	}
	if (!found)
		return (error_msg("missing player spawn"));
	return (EXIT_SUCCESS);
}

int	validate_map(t_config *cfg)
{
	/*
	** SKELETON ONLY:
	** - Minimal checks to keep flow working for integration.
	** - Mandatory robust validation (full charset control + closure flood-fill)
	**   is intentionally left for your implementation.
	*/

	if (cfg->map.height <= 0 || cfg->map.width <= 0 || !cfg->map.grid)
		return (error_msg("empty map"));
	if (find_single_spawn_skeleton(cfg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
