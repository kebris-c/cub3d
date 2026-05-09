/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/30 13:09:53 by kjroydev         ###   ########.fr       */
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
	if (ft_strchr(value, ' ') || ft_strchr(value, '\t'))
		return (error_msg("texture path must be a single token"));
	if (!file_has_extension(value, ".xpm"))
		return (error_msg("texture path must end with .xpm"));
	if (access(value, R_OK) != 0)
		return (error_msg("texture path is missing or unreadable"));
	cfg->tex_path[id] = ft_strdup(value);
	if (!cfg->tex_path[id])
		return (error_msg("malloc failed"));
	return (EXIT_SUCCESS);
}

static int	parse_identifier_line(t_config *cfg, const char *id,
	const char *value)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (assign_texture_path(cfg, NO, value));
	if (ft_strncmp(id, "SO", 3) == 0)
		return (assign_texture_path(cfg, SO, value));
	if (ft_strncmp(id, "WE", 3) == 0)
		return (assign_texture_path(cfg, WE, value));
	if (ft_strncmp(id, "EA", 3) == 0)
		return (assign_texture_path(cfg, EA, value));
	if (ft_strncmp(id, "F", 2) == 0)
	{
		if (cfg->floor_color != -1)
			return (error_msg("duplicated F color"));
		return (parser_parse_rgb_components(value, &cfg->floor_color));
	}
	if (ft_strncmp(id, "C", 2) == 0)
	{
		if (cfg->ceil_color != -1)
			return (error_msg("duplicated C color"));
		return (parser_parse_rgb_components(value, &cfg->ceil_color));
	}
	return (error_msg("unknown identifier in header"));
}

int	parse_header_line(t_config *cfg, const char *line)
{
	size_t	i;
	char	*id;
	char	*value;
	int		ret;

	i = 0;
	id = parser_next_token(line, &i);
	if (!id)
		return (EXIT_SUCCESS);
	value = parser_next_token(line, &i);
	if (!value)
		return (free(id), error_msg("header value missing"));
	ret = parser_header_line_has_no_trailing_tokens(line, i);
	if (ret == EXIT_SUCCESS)
		ret = parse_identifier_line(cfg, id, value);
	free(value);
	free(id);
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
