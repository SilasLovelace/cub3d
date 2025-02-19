/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:01:47 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/19 15:36:48 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_ray_params(t_ray *ray, int parse_density)
{
	t_memory	*mem;

	mem = get_memory();
	if (ray->ray_num == 0)
	{
		ray->angle_per_pixel = FOV / mem->mlx_data->resolution_x;
		ray->angle = mem->player_pos->angle - M_PI / 6;
	}
	ray->ray_x = mem->player_pos->x;
	ray->ray_y = mem->player_pos->y;
	ray->step_x = cos(ray->angle) / parse_density;
	ray->step_y = sin(ray->angle) / parse_density;
}

int	is_inbound(t_ray *ray)
{
	t_memory	*mem;

	mem = get_memory();
	return (ray->ray_x > 0 && ray->ray_x < mem->resources->map_width
		&& ray->ray_y > 0 && ray->ray_y < mem->resources->map_height);
}

void	increment_step(t_ray *ray)
{
	ray->last_x = (int)ray->ray_x;
	ray->last_y = (int)ray->ray_y;
	ray->ray_x += ray->step_x;
	ray->ray_y += ray->step_y;
}

int	get_mlx_img_pixel_color(t_texture *tex, int x, int y)
{
	return (*(unsigned int *)(tex->addr + \
		(y * tex->line_length + x * (tex->bpp / 8))));
}
