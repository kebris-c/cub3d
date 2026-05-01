/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 17:57:37 by kjroydev          #+#    #+#             */
/*   Updated: 2026/05/01 17:17:08 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex_id	get_tex_id(t_ray *ray)
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

void	get_direction(t_ray *ray)
{
	t_tex_id	id;

	id = get_tex_id(ray);
	if (id >= 0 && id < 4)
		ray->dir_id = id;
}
