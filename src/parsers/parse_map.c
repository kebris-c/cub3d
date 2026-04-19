#include "cub3d.h"

static int	build_map_grid(t_config *cfg, char **lines, int start)
{
	int		i;
	int		j;
	size_t	len;

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
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	parse_map_block(t_config *cfg, char **lines, int start)
{
	int		i;
	size_t	len;

	if (!lines[start])
		return (error_msg("missing map block"));
	i = start;
	cfg->map.width = 0;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
			return (error_msg("empty line inside map"));
		if (!is_map_line(lines[i]))
			return (error_msg("invalid map line"));
		len = line_len_no_nl(lines[i]);
		if ((int)len > cfg->map.width)
			cfg->map.width = (int)len;
		i++;
	}
	if (cfg->map.width <= 0)
		return (error_msg("invalid map width"));
	return (build_map_grid(cfg, lines, start));
}

int	parse_cub_file(t_config *cfg, const char *path)
{
	char	**lines;
	int		i;
	int		header_count;

	lines = NULL;
	if (load_file_lines(path, &lines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	header_count = 0;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_map_line(lines[i]))
			break ;
		if (parse_header_line(cfg, lines[i]) == EXIT_FAILURE)
			return (free_lines(lines), EXIT_FAILURE);
		header_count++;
		i++;
	}
	if (header_count != 6)
		return (free_lines(lines),
			error_msg("header must have exactly 6 entries"));
	if (!headers_complete(cfg))
		return (free_lines(lines), error_msg("incomplete header"));
	while (lines[i] && is_blank_line(lines[i]))
		i++;
	if (parse_map_block(cfg, lines, i) == EXIT_FAILURE)
		return (free_lines(lines), EXIT_FAILURE);
	free_lines(lines);
	/*
	** TODO (validation): Replace this relaxed call with full mandatory checks:
	** allowed chars, exactly one spawn, and closed map (flood fill).
	*/
	return (validate_map(cfg));
}
