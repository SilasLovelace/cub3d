/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:23 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 13:29:48 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void reset_ray_params(t_ray *ray, int parse_density)
{
	t_memory	*mem;
	
	mem = get_memory();
	if (ray->ray_num == 0)
	{
		ray->angle_per_pixel = M_PI/3 / mem->mlx_data->resolution_x;
		ray->angle = mem->player_pos->angle - M_PI/6;	
	}
	ray->ray_x = mem->player_pos->x;
	ray->ray_y = mem->player_pos->y;
	ray->step_x = cos(ray->angle) / parse_density;
	ray->step_y = sin(ray->angle) / parse_density;
}

void		cast_rays()
{
	t_memory	*mem;
	t_ray		*ray;
	
	ray = ft_calloc(sizeof(t_ray), 1);
	mem = get_memory();	
	while (ray->ray_num < mem->mlx_data->resolution_x)
	{
		reset_ray_params(ray, PARSE_DENSITY);
		while (ray->ray_x > 0 && ray->ray_x < mem->resources->map_width
			&& ray->ray_y > 0 && ray->ray_y < mem->resources->map_height
			&& mem->map[(int)ray->ray_y][(int)ray->ray_x] != '1')
		{
			ray->last_x = (int)ray->ray_x;
			ray->last_y = (int)ray->ray_y;
			ray->ray_x += ray->step_x;
			ray->ray_y += ray->step_y;
			if ((int)ray->ray_x != ray->last_x || (int)ray->ray_y != ray->last_y)
			{
				if (mem->map[(int)ray->ray_y][(int)ray->ray_x] == '1')
				{
					if((int)ray->ray_x > ray->last_x)
					{
						ray->tex_num = WEST;
						ray->tex_x = (int)((ray->ray_y - (int)ray->ray_y) * mem->mlx_data->textures[WEST].width);
					}
					else if ((int)ray->ray_x < ray->last_x)
					{
						ray->tex_num = EAST;
						ray->tex_x = (int)(1 - (ray->ray_y - (int)ray->ray_y) * mem->mlx_data->textures[EAST].width);
					}
					else if ((int)ray->ray_y > ray->last_y)
					{
						ray->tex_num = NORTH;
						ray->tex_x = (int)(1 - (ray->ray_x - (int)ray->ray_x) * mem->mlx_data->textures[NORTH].width);
					}
					else if ((int)ray->ray_y < ray->last_y)
					{
						ray->tex_num = SOUTH;
						ray->tex_x = (int)((ray->ray_x - (int)ray->ray_x) * mem->mlx_data->textures[SOUTH].width);
					}
					double distance = sqrt((ray->ray_x - mem->player_pos->x) * (ray->ray_x - mem->player_pos->x)
										+ (ray->ray_y - mem->player_pos->y) * (ray->ray_y - mem->player_pos->y));
					ray->line_height = mem->mlx_data->resolution_y / (distance * cos(ray->angle - mem->player_pos->angle));
					ray->draw_start = -ray->line_height / 2 + mem->mlx_data->resolution_y / 2;
					ray->draw_end = ray->line_height / 2 + mem->mlx_data->resolution_y / 2;
					t_texture tex = mem->mlx_data->textures[ray->tex_num];
					int y = 0;
					while (y < mem->mlx_data->resolution_y)
					{
						if(y < ray->draw_start)
						{
							my_mlx_pixel_put(ray->ray_num, y, mem->resources->ceiling_color);
						}
						else if (y > ray->draw_end)
						{
							my_mlx_pixel_put(ray->ray_num, y, mem->resources->floor_color);
						}
						else
						{
							int tex_y = (int)((y - ray->draw_start) * (double)tex.height / (ray->draw_end - ray->draw_start));
							tex_y = (tex_y < 0) ? 0 : tex_y;
							tex_y = (tex_y >= tex.height) ? tex.height - 1 : tex_y;
							unsigned int color = *(unsigned int*)(tex.addr + (tex_y * tex.line_length + ray->tex_x * (tex.bpp / 8)));
								my_mlx_pixel_put(ray->ray_num, y, color);
						}
						y++;
					} 
					break;
				}
			}
		}
		ray->ray_num++;
		ray->angle += ray->angle_per_pixel;
	}
	free(ray);
}


// #include "../../includes/cub3d.h"
// bool is_inbound(t_ray *ray)
// {
// 	t_memory	*mem;
	
// 	mem = get_memory();
// 	return(ray->ray_x > 0 && ray->ray_x < mem->resources->map_width
// 			&& ray->ray_y > 0 && ray->ray_y < mem->resources->map_height);
// 	// return(ray->ray_x > 0 && ray->ray_x < mem->resources->map_width
// 			// && ray->ray_y > 0 && ray->ray_y < mem->resources->map_height
// 			// && mem->map[(int)ray->ray_y][(int)ray->ray_x] != '1')
// }


// void reset_ray_params(t_ray *ray, int parse_density)
// {
// 	t_memory	*mem;
	
// 	mem = get_memory();
// 	if (ray->ray_num == 0)
// 	{
// 		ray->angle_per_pixel = M_PI/3 / mem->mlx_data->resolution_x;
// 		ray->angle = mem->player_pos->angle - M_PI/6;	
// 	}
// 	ray->ray_x = mem->player_pos->x;
// 	ray->ray_y = mem->player_pos->y;
// 	ray->step_x = cos(ray->angle) / parse_density;
// 	ray->step_y = sin(ray->angle) / parse_density;
// }

// void increment_step(t_ray *ray)
// {
// 	ray->last_x = (int)ray->ray_x;
// 	ray->last_y = (int)ray->ray_y;
// 	ray->ray_x += ray->step_x;
// 	ray->ray_y += ray->step_y;
// }
// void find_texture_intersect(t_ray *ray)
// {
// 	t_memory	*mem;
	
// 	mem = get_memory();
// 	if((int)ray->ray_x > ray->last_x)
// 	{
// 		ray->tex_num = WEST;
// 		ray->tex_x = (int)((ray->ray_y - (int)ray->ray_y) * mem->mlx_data->textures[WEST].width);
// 	}
// 	else if ((int)ray->ray_x < ray->last_x)
// 	{
// 		ray->tex_num = EAST;
// 		ray->tex_x = (int)(1 - (ray->ray_y - (int)ray->ray_y) * mem->mlx_data->textures[EAST].width);
// 	}
// 	else if ((int)ray->ray_y > ray->last_y)
// 	{
// 		ray->tex_num = NORTH;
// 		ray->tex_x = (int)(1 - (ray->ray_x - (int)ray->ray_x) * mem->mlx_data->textures[NORTH].width);
// 	}
// 	else if ((int)ray->ray_y < ray->last_y)
// 	{
// 		ray->tex_num = SOUTH;
// 		ray->tex_x = (int)((ray->ray_x - (int)ray->ray_x) * mem->mlx_data->textures[SOUTH].width);
// 	}
// }

// unsigned int get_pixel_color_from_mlx_img(t_texture *tex, int x, int y)
// {
// 	return (*(unsigned int*)(tex->addr + (y * tex->line_length + x * (tex->bpp / 8))));
// }
// void find_and_draw_texture_line(t_ray *ray)
// {
// 	t_memory	*mem;
// 	t_texture	tex;

// 	mem = get_memory();
// 	ray->y_iterator = 0;
// 	ray->distance = sqrt((ray->ray_x - mem->player_pos->x) * (ray->ray_x - mem->player_pos->x)
// 										+ (ray->ray_y - mem->player_pos->y) * (ray->ray_y - mem->player_pos->y));
// 	ray->draw_start = -ray->line_height / 2 + mem->mlx_data->resolution_y / 2;
// 	ray->draw_end = ray->line_height / 2 + mem->mlx_data->resolution_y / 2;
// 	tex = mem->mlx_data->textures[ray->tex_num];
// 	while (ray->y_iterator < mem->mlx_data->resolution_y)
// 	{
// 		if(ray->y_iterator < ray->draw_start)
// 			my_mlx_pixel_put(ray->ray_num, ray->y_iterator, mem->resources->ceiling_color);
// 		else if (ray->y_iterator > ray->draw_end)
// 			my_mlx_pixel_put(ray->ray_num, ray->y_iterator, mem->resources->floor_color);
// 		else
// 		{
// 			int tex_y = (int)((ray->y_iterator - ray->draw_start) * (double)tex.height / (ray->draw_end - ray->draw_start));
// 			tex_y = (tex_y < 0) ? 0 : tex_y;
// 			tex_y = (tex_y >= tex.height) ? tex.height - 1 : tex_y;
// 			my_mlx_pixel_put(ray->ray_num, ray->y_iterator, get_pixel_color_from_mlx_img(&tex, ray->tex_x, tex_y));
// 		}
// 		ray->y_iterator++;
// 	} 
// }
// void		cast_rays()
// {
// 	t_memory	*mem;
// 	t_ray		*ray;
	
// 	ray = ft_calloc(sizeof(t_ray), 1);
// 	mem = get_memory();	
// 	while (ray->ray_num < mem->mlx_data->resolution_x)
// 	{
// 		reset_ray_params(ray, PARSE_DENSITY);
// 		while (is_inbound(ray))
// 		{
// 			increment_step(ray);
// 			if ((int)ray->ray_x != ray->last_x || (int)ray->ray_y != ray->last_y)
// 			{
// 				if (mem->map[(int)ray->ray_y][(int)ray->ray_x] == '1')
// 				{
// 					find_texture_intersect(ray);
// 					find_and_draw_texture_line(ray);
// 					break;
// 				}
// 			}
// 		}
// 		ray->ray_num++;
// 		ray->angle += ray->angle_per_pixel;
// 	}
// 	free(ray);
// }
