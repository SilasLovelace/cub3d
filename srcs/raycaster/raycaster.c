/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:23 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/13 15:59:58 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_texture_dimensions(char *filepath)
{
	char		*line;
	int			fd;
	int			i;
	bool		flag;
	t_memory	*memory;

	flag = false;
	memory = get_memory();
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return ;
	for (int j = 0; j < 3; j++)
	{
		line = get_next_line(fd, &flag, false);
		if (flag)
		{
			printf("Error! Memory allocation failed\n");
			free_memory();
			exit(1);
		}
		if (line)
			free(line);
	}
	line = get_next_line(fd, &flag, false);
	if (flag)
	{
		printf("Error! Memory allocation failed\n");
		free_memory();
		exit(1);
	}
	if (!line)
	{
		close(fd);
		return ;
	}
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '"'))
		i++;
	memory->mlx_data->tex_width = ft_atoi(line + i);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	memory->mlx_data->tex_height = ft_atoi(line + i);
	get_next_line(fd, false, true);
	free(line);
	close(fd);
}

void		cast_rays()
{
	t_memory	*mem;
	t_ray		*ray;
	int			ray_num;
	float		angle_per_pixel;
	
	ray = malloc(sizeof(t_ray));
	ray_num = 0;
	mem = get_memory();
	angle_per_pixel = M_PI/3 / mem->mlx_data->resolution_x;
	ray->angle = mem->player_pos->angle - M_PI/6;		
	while (ray_num < mem->mlx_data->resolution_x)
	{
		ray->ray_x = mem->player_pos->x;
		ray->ray_y = mem->player_pos->y;
		// if (ray_num == 960)
		// {
		// 	printf("player angle %f\n", mem->player_pos->angle/M_PI);
		// 	// int direction_x = (ray->angle/M_PI > 0.5 || ray->angle/M_PI < -0.5) ? -1 : 1;
		// 	int direction_x = (cos(ray->angle) > 0) ? 1 : -1;
		// 	printf("direction_x: %d\n", direction_x);
		// 	if (direction_x < 0)
		// 		ray->step_x = (ray->ray_x - (int)(ray->ray_x)) * direction_x;
		// 	else if (direction_x > 0)
		// 	    ray->step_x = (int)(ray->ray_x + 1) - ray->ray_x;
		// 	else
		// 		ray->step_x = 0;
		// 	printf("step_x: %f\n", ray->step_x);
		// 	int direction_y = (sin(ray->angle) > 0) ? 1 : -1;
		// 	printf("direction_y: %d\n", direction_y);
		// 	printf("tan: %f\n", tan(ray->angle));
		// 	ray->step_y = (ray->step_x * tan(ray->angle));
		// 	printf("step_y: %f\n", ray->step_y);
		// 	ray->ray_x += ray->step_x;
		// 	ray->ray_y += ray->step_y;
		// 	printf("player coords x: %f, y: %f\n", mem->player_pos->x, mem->player_pos->y);
		// 	printf("intersextion x: %f, y: %f\n", ray->ray_x, ray->ray_y);
		// 	printf("is wall %c\n", mem->map[(int)ray->ray_y][(int)ray->ray_x] == '1' ? 'y' : 'n');
		// }
		
		ray->step_x = cos(ray->angle) / 1000;
		ray->step_y = sin(ray->angle) / 1000;
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
						ray->tex_x = (int)((ray->ray_y - (int)ray->ray_y) * mem->mlx_data->tex_width);
					}
					else if ((int)ray->ray_x < ray->last_x)
					{
						ray->tex_num = EAST;
						ray->tex_x = (int)((ray->ray_y - (int)ray->ray_y) * mem->mlx_data->tex_width);
					}
					else if ((int)ray->ray_y > ray->last_y)
					{
						ray->tex_num = NORTH;
						ray->tex_x = (int)((ray->ray_x - (int)ray->ray_x) * mem->mlx_data->tex_width);
					}
					else if ((int)ray->ray_y < ray->last_y)
					{
						ray->tex_num = SOUTH;
						ray->tex_x = (int)((ray->ray_x - (int)ray->ray_x) * mem->mlx_data->tex_width);
					}
					float distance = sqrt((ray->ray_x - mem->player_pos->x) * (ray->ray_x - mem->player_pos->x)
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
							my_mlx_pixel_put(ray_num, y, mem->resources->ceiling_color);
						}
						else if (y > ray->draw_end)
						{
							my_mlx_pixel_put(ray_num, y, mem->resources->floor_color);
						}
						else
						{
							int tex_y = (int)((y - ray->draw_start) * (double)512 / (ray->draw_end - ray->draw_start));
							tex_y = (tex_y < 0) ? 0 : tex_y;
							tex_y = (tex_y >= 512) ? 512 - 1 : tex_y;
							unsigned int color = *(unsigned int*)(tex.addr + (tex_y * tex.line_length + ray->tex_x * (tex.bpp / 8)));
								my_mlx_pixel_put(ray_num, y, color);
						}
						y++;
					} 
					break;
				}
			}
		}
		ray_num++;
		ray->angle += angle_per_pixel;
	}
	free(ray);
}
