#include "cub3d.h"

static int	count_lines_fd(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static int	fill_lines_fd(int fd, char **lines, int total)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line && i < total)
	{
		lines[i] = line;
		i++;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	if (line)
		free(line);
	return (EXIT_SUCCESS);
}

int	load_file_lines(const char *path, char ***lines)
{
	int	fd;
	int	total;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("cannot open .cub file"));
	total = count_lines_fd(fd);
	close(fd);
	if (total <= 0)
		return (error_msg("empty .cub file"));
	*lines = ft_calloc((size_t)total + 1, sizeof(char *));
	if (!*lines)
		return (error_msg("malloc failed"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(*lines), *lines = NULL, error_msg("cannot reopen .cub file"));
	fill_lines_fd(fd, *lines, total);
	close(fd);
	return (EXIT_SUCCESS);
}

void	free_lines(char **lines)
{
	ft_free_matrix(lines);
}
