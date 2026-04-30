/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 17:57:37 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/30 08:41:26 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex_id	get_tex_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (ray->dir_y > 0)
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
