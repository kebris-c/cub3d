/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c        #+#    #+#               */
/*   Updated: 2026/04/20 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Top-level .cub orchestration: consumes header lines until the map block,
** enforces the six mandatory header rows, then delegates grid fill and
** spawn validation to parse_map_grid / map_validate.
*/
static int	read_header_section(t_config *cfg, char **lines, int *i,
	int *header_count)
{
	*i = 0;
	*header_count = 0;
	while (lines[*i])
	{
		if (is_blank_line(lines[*i]))
		{
			(*i)++;
			continue ;
		}
		if (is_map_line(lines[*i]))
			break ;
		if (parse_header_line(cfg, lines[*i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*header_count)++;
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

static int	check_headers_complete(t_config *cfg, char **lines, int count)
{
	if (count != 6)
		return (free_lines(lines),
			error_msg("header must have exactly 6 entries"));
	if (!headers_complete(cfg))
		return (free_lines(lines), error_msg("incomplete header"));
	return (EXIT_SUCCESS);
}

int	parse_cub_file(t_config *cfg, const char *path)
{
	char	**lines;
	int		i;
	int		header_count;

	lines = NULL;
	if (load_file_lines(path, &lines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (read_header_section(cfg, lines, &i, &header_count) == EXIT_FAILURE)
		return (free_lines(lines), EXIT_FAILURE);
	if (check_headers_complete(cfg, lines, header_count) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (lines[i] && is_blank_line(lines[i]))
		i++;
	if (parse_map_into_cfg(cfg, lines, i) == EXIT_FAILURE)
		return (free_lines(lines), EXIT_FAILURE);
	free_lines(lines);
	return (validate_map(cfg));
}
