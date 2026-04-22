/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/22 00:00:00 by kebris-c        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Map grid: contiguous non-blank map lines, reject inner blanks, optional
** blanks only after the block, then reject any further non-blank line.
*/
static int	map_line_push_metrics(const char *line, int *w, int *h)
{
	size_t	len;

	if (!is_map_line(line))
		return (error_msg("invalid map line"));
	len = line_len_no_nl(line);
	if ((int)len > *w)
		*w = (int)len;
	(*h)++;
	return (EXIT_SUCCESS);
}

static int	scan_map_block(char **lines, int start, t_config *cfg, int *next)
{
	int	i;
	int	w;
	int	h;

	if (!lines[start] || is_blank_line(lines[start]))
		return (error_msg("missing map block"));
	h = 0;
	w = 0;
	i = start;
	while (lines[i] && !is_blank_line(lines[i]))
	{
		if (map_line_push_metrics(lines[i], &w, &h) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (w <= 0 || h <= 0)
		return (error_msg("invalid map size"));
	cfg->map.height = h;
	cfg->map.width = w;
	*next = i;
	return (EXIT_SUCCESS);
}

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
			cfg->map.grid[i][j] = '0';
		j++;
	}
	return (EXIT_SUCCESS);
}

static int	build_map_grid(t_config *cfg, char **lines, int start)
{
	int		i;

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

int	parse_map_into_cfg(t_config *cfg, char **lines, int start)
{
	int	next;

	if (scan_map_block(lines, start, cfg, &next) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (build_map_grid(cfg, lines, start) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (lines[next] && is_blank_line(lines[next]))
		next++;
	if (lines[next])
		return (error_msg("trailing content after map"));
	return (EXIT_SUCCESS);
}
