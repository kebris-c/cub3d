/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c        #+#    #+#               */
/*   Updated: 2026/04/20 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Map grid construction: scan map lines for max width, reject inner blanks,
** pad short rows with spaces, allocate cfg->map.grid for the renderer.
*/
static int	fill_row_from_line(t_config *cfg, char **lines, int start, int i)
{
	size_t	len;
	int		j;

	len = line_len_no_nl(lines[start + i]);
	cfg->map.grid[i] = ft_calloc((size_t)cfg->map.width + 1, sizeof(char));
	if (!cfg->map.grid[i])
		return (error_msg("malloc failed"));
	j = 0;
	while (j < cfg->map.width)
	{
		if ((size_t)j < len)
			cfg->map.grid[i][j] = lines[start + i][j];
		else
			cfg->map.grid[i][j] = ' ';
		j++;
	}
	return (EXIT_SUCCESS);
}

static int	build_map_grid(t_config *cfg, char **lines, int start)
{
	int		i;

	i = 0;
	while (lines[start + i])
		i++;
	cfg->map.height = i;
	cfg->map.grid = ft_calloc((size_t)cfg->map.height + 1, sizeof(char *));
	if (!cfg->map.grid)
		return (error_msg("malloc failed"));
	i = 0;
	while (i < cfg->map.height)
	{
		if (fill_row_from_line(cfg, lines, start, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	measure_map_width(char **lines, int start)
{
	int		i;
	size_t	len;
	int		width;

	i = start;
	width = 0;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
			return (-1);
		if (!is_map_line(lines[i]))
			return (-1);
		len = line_len_no_nl(lines[i]);
		if ((int)len > width)
			width = (int)len;
		i++;
	}
	return (width);
}

int	parse_map_into_cfg(t_config *cfg, char **lines, int start)
{
	int	width;

	if (!lines[start])
		return (error_msg("missing map block"));
	width = measure_map_width(lines, start);
	if (width <= 0)
		return (error_msg("invalid map width"));
	cfg->map.width = width;
	return (build_map_grid(cfg, lines, start));
}
