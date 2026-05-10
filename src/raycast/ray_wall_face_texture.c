/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall_face_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 17:57:37 by kjroydev          #+#    #+#             */
/*   Updated: 2026/05/01 17:17:08 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex_id	wall_texture_id_from_ray_step(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (WE);
		else
			return (EA);
	}
	else
	{
		if (ray->step_y > 0)
			return (NO);
		else
			return (SO);
	}
}

void	ray_assign_wall_texture_by_hit_side(t_ray *ray)
{
	t_tex_id	id;

	id = wall_texture_id_from_ray_step(ray);
	if (id >= 0 && id < 4)
		ray->dir_id = id;
}
