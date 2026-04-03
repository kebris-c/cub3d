#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	is_walkable(t_map *map, double x, double y)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)x;
	cell_y = (int)y;
	if (cell_x < 0 || cell_x >= map->width || cell_y < 0 || cell_y >= map->height)
		return (0);
	return (map->grid[cell_y][cell_x] == '0');
}
