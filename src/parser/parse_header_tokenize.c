/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_tokenize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_ws(int c)
{
	return (c == ' ' || c == '\t');
}

char	*parser_next_token(const char *s, size_t *i)
{
	size_t	start;
	size_t	end;

	while (s[*i] && is_ws((unsigned char)s[*i]))
		(*i)++;
	start = *i;
	while (s[*i] && !is_ws((unsigned char)s[*i]) && s[*i] != '\n')
		(*i)++;
	end = *i;
	if (end == start)
		return (NULL);
	return (ft_substr(s, start, end - start));
}

int	parser_header_line_has_no_trailing_tokens(const char *s, size_t i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if (s[i])
		return (error_msg("extra tokens in header line"));
	return (EXIT_SUCCESS);
}

static int	parse_rgb_component(const char *value, size_t *i, int *out)
{
	long	v;

	while (value[*i] && is_ws((unsigned char)value[*i]))
		(*i)++;
	if (!ft_isdigit((unsigned char)value[*i]))
		return (error_msg("invalid RGB format"));
	v = 0;
	while (ft_isdigit((unsigned char)value[*i]))
	{
		v = v * 10 + (value[*i] - '0');
		(*i)++;
	}
	while (value[*i] && is_ws((unsigned char)value[*i]))
		(*i)++;
	if (v < 0 || v > 255)
		return (error_msg("RGB value out of range"));
	*out = (int)v;
	return (EXIT_SUCCESS);
}

int	parser_parse_rgb_components(const char *value, int *out_color)
{
	int		rgb[3];
	size_t	i;

	i = 0;
	if (parse_rgb_component(value, &i, &rgb[0]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (value[i++] != ',')
		return (error_msg("invalid RGB format"));
	if (parse_rgb_component(value, &i, &rgb[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (value[i++] != ',')
		return (error_msg("invalid RGB format"));
	if (parse_rgb_component(value, &i, &rgb[2]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (value[i] && (value[i] == ' ' || value[i] == '\t'))
		i++;
	if (value[i] == '\n')
		i++;
	if (value[i])
		return (error_msg("extra tokens in RGB value"));
	*out_color = rgb_to_int(rgb[0], rgb[1], rgb[2]);
	return (EXIT_SUCCESS);
}
