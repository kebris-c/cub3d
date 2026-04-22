/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c        #+#    #+#               */
/*   Updated: 2026/04/22 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Header: NO/SO/WE/EA paths (.xpm, readable), F/C RGB strict digits [0,255].
*/
static int	assign_texture_path(t_config *cfg, int id, const char *value)
{
	if (cfg->tex_path[id])
		return (error_msg("duplicated texture identifier"));
	if (!file_has_extension(value, ".xpm"))
		return (error_msg("texture path must end with .xpm"));
	if (access(value, R_OK) != 0)
		return (error_msg("texture path is missing or unreadable"));
	cfg->tex_path[id] = ft_strdup(value);
	if (!cfg->tex_path[id])
		return (error_msg("malloc failed"));
	return (EXIT_SUCCESS);
}

static int	parse_rgb_triplet(const char *value, int *out_color)
{
	char	**parts;
	int		rgb[3];
	int		i;
	size_t	j;

	parts = ft_split(value, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_free_matrix(parts), error_msg("invalid RGB format"));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (parts[i][j] && ft_isdigit((unsigned char)parts[i][j]))
			j++;
		if (j == 0 || parts[i][j])
			return (ft_free_matrix(parts), error_msg("invalid RGB format"));
		rgb[i] = ft_atoi(parts[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_free_matrix(parts), error_msg("RGB value out of range"));
		i++;
	}
	*out_color = rgb_to_int(rgb[0], rgb[1], rgb[2]);
	return (ft_free_matrix(parts), EXIT_SUCCESS);
}

static int	parse_identifier_line(t_config *cfg, const char *id,
	const char *value)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (assign_texture_path(cfg, TEX_NO, value));
	if (ft_strncmp(id, "SO", 3) == 0)
		return (assign_texture_path(cfg, TEX_SO, value));
	if (ft_strncmp(id, "WE", 3) == 0)
		return (assign_texture_path(cfg, TEX_WE, value));
	if (ft_strncmp(id, "EA", 3) == 0)
		return (assign_texture_path(cfg, TEX_EA, value));
	if (ft_strncmp(id, "F", 2) == 0)
	{
		if (cfg->floor_color != -1)
			return (error_msg("duplicated F color"));
		return (parse_rgb_triplet(value, &cfg->floor_color));
	}
	if (ft_strncmp(id, "C", 2) == 0)
	{
		if (cfg->ceil_color != -1)
			return (error_msg("duplicated C color"));
		return (parse_rgb_triplet(value, &cfg->ceil_color));
	}
	return (error_msg("unknown identifier in header"));
}

int	parse_header_line(t_config *cfg, const char *line)
{
	char	*trimmed;
	char	*space;
	char	*id;
	char	*value;
	int		ret;

	trimmed = trim_spaces(line);
	if (!trimmed || !*trimmed)
		return (free(trimmed), EXIT_SUCCESS);
	space = ft_strchr(trimmed, ' ');
	if (!space)
		return (free(trimmed), error_msg("header line missing value"));
	*space = '\0';
	id = trimmed;
	value = trim_spaces(space + 1);
	if (!value || !*value)
		return (free(value), free(trimmed), error_msg("header value missing"));
	ret = parse_identifier_line(cfg, id, value);
	free(value);
	free(trimmed);
	return (ret);
}

int	headers_complete(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (!cfg->tex_path[i])
			return (0);
		i++;
	}
	if (cfg->floor_color == -1 || cfg->ceil_color == -1)
		return (0);
	return (1);
}
