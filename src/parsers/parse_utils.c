#include "cub3d.h"

int	error_msg(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg && *msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (EXIT_FAILURE);
}

size_t	line_len_no_nl(const char *line)
{
	size_t	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

int	is_blank_line(const char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*trim_spaces(const char *line)
{
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	end = line_len_no_nl(line);
	while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
		end--;
	len = end - start;
	return (ft_substr(line, start, len));
}

int	file_has_extension(const char *file, const char *ext)
{
	size_t	f_len;
	size_t	e_len;

	if (!file || !ext)
		return (0);
	f_len = ft_strlen(file);
	e_len = ft_strlen(ext);
	if (f_len <= e_len)
		return (0);
	return (ft_strncmp(file + (f_len - e_len), ext, e_len) == 0);
}
