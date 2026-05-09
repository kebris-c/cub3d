/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosure_bfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by kebris-c          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by kebris-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Breadth-first search from the player cell. Any boundary hit outside the
** grid, a space tile (void), or an unvisited walkable expands the frontier.
** If we ever touch void/outside, the playable area is not fully enclosed.
**
** BFS visits map cells level-by-level from the spawn. We use it only to
** prove the walkable region does not leak into void (space) or outside the
** rectangle; DFS would also work for this property.
*/

static int	bfs_try_visit_neighbor(t_map_bfs_ctx *ctx, int nx, int ny)
{
	int	idx;

	if (nx < 0 || ny < 0)
		return (EXIT_FAILURE);
	if (nx >= ctx->cfg->map.width || ny >= ctx->cfg->map.height)
		return (EXIT_FAILURE);
	if (ctx->cfg->map.grid[ny][nx] == ' ')
		return (EXIT_FAILURE);
	if (ctx->cfg->map.grid[ny][nx] == '1')
		return (EXIT_SUCCESS);
	idx = ny * ctx->cfg->map.width + nx;
	if (ctx->visited[idx])
		return (EXIT_SUCCESS);
	ctx->visited[idx] = 1;
	ctx->queue[ctx->queue_tail++] = idx;
	return (EXIT_SUCCESS);
}

static int	bfs_pop_front_and_expand_neighbors(t_map_bfs_ctx *ctx)
{
	int	idx;
	int	x;
	int	y;

	idx = ctx->queue[ctx->queue_head++];
	x = idx % ctx->cfg->map.width;
	y = idx / ctx->cfg->map.width;
	if (bfs_try_visit_neighbor(ctx, x + 1, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (bfs_try_visit_neighbor(ctx, x - 1, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (bfs_try_visit_neighbor(ctx, x, y + 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (bfs_try_visit_neighbor(ctx, x, y - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validate_map_is_closed_bfs(t_config *cfg)
{
	unsigned char	*visited;
	int				*queue;
	t_map_bfs_ctx	ctx;
	int				spawn_idx;

	visited = ft_calloc((size_t)(cfg->map.width * cfg->map.height), 1);
	queue = ft_calloc((size_t)(cfg->map.width * cfg->map.height), sizeof(int));
	if (!visited || !queue)
		return (free(visited), free(queue), error_msg("malloc failed"));
	ctx.cfg = cfg;
	ctx.visited = visited;
	ctx.queue = queue;
	ctx.queue_head = 0;
	ctx.queue_tail = 0;
	spawn_idx = ((int)cfg->player_y) * cfg->map.width + (int)cfg->player_x;
	ctx.visited[spawn_idx] = 1;
	ctx.queue[ctx.queue_tail++] = spawn_idx;
	while (ctx.queue_head < ctx.queue_tail)
		if (bfs_pop_front_and_expand_neighbors(&ctx) == EXIT_FAILURE)
			return (free(visited), free(queue), error_msg("map is open"));
	return (free(visited), free(queue), EXIT_SUCCESS);
}
