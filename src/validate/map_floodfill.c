/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	push_neighbor(t_ff_state *st, int nx, int ny)
{
	int	idx;

	if (nx < 0 || ny < 0
		|| nx >= st->cfg->map.width
		|| ny >= st->cfg->map.height)
		return (EXIT_FAILURE);
	if (st->cfg->map.grid[ny][nx] == ' ')
		return (EXIT_FAILURE);
	if (st->cfg->map.grid[ny][nx] == '1')
		return (EXIT_SUCCESS);
	idx = ny * st->cfg->map.width + nx;
	if (st->seen[idx])
		return (EXIT_SUCCESS);
	st->seen[idx] = 1;
	st->q[st->ht[1]++] = idx;
	return (EXIT_SUCCESS);
}

static int	expand_one(t_ff_state *st)
{
	int	idx;
	int	x;
	int	y;

	idx = st->q[st->ht[0]++];
	x = idx % st->cfg->map.width;
	y = idx / st->cfg->map.width;
	if (push_neighbor(st, x + 1, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (push_neighbor(st, x - 1, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (push_neighbor(st, x, y + 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (push_neighbor(st, x, y - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map_is_closed(t_config *cfg)
{
	unsigned char	*seen;
	int				*q;
	t_ff_state		st;
	int				sidx;

	seen = ft_calloc((size_t)(cfg->map.width * cfg->map.height), 1);
	q = ft_calloc((size_t)(cfg->map.width * cfg->map.height), sizeof(int));
	if (!seen || !q)
		return (free(seen), free(q), error_msg("malloc failed"));
	st.cfg = cfg;
	st.seen = seen;
	st.q = q;
	st.ht[0] = 0;
	st.ht[1] = 0;
	sidx = ((int)cfg->player_y) * cfg->map.width + (int)cfg->player_x;
	st.seen[sidx] = 1;
	st.q[st.ht[1]++] = sidx;
	while (st.ht[0] < st.ht[1])
		if (expand_one(&st) == EXIT_FAILURE)
			return (free(seen), free(q), error_msg("map is open"));
	return (free(seen), free(q), EXIT_SUCCESS);
}
