/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:13:16 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/24 11:24:32 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	precal_camera_factors(double *cam_factor)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cam_factor[x] = 2.0 * x / (double)(WIN_WIDTH - 1) - 1.0;
		x++;
	}
}
