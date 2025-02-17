/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:23 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/17 16:12:06 by sopperma         ###   ########.fr       */
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
	double		angle_per_pixel;
	
	ray = malloc(sizeof(t_ray));
	ray_num = 0;
	mem = get_memory();
	angle_per_pixel = M_PI/3 / mem->mlx_data->resolution_x;
	ray->angle = mem->player_pos->angle - M_PI/6;		
	while (ray_num < mem->mlx_data->resolution_x)
	{
		ray->ray_x = mem->player_pos->x;
		ray->ray_y = mem->player_pos->y;
	 if (ray_num == 320)  // Debug ray
	 {
		
        // 1. Calculate ray direction
        double ray_dir_x = cos(ray->angle);
        double ray_dir_y = sin(ray->angle);

        // 2. Calculate which box of the map we're in
        int map_x = (int)mem->player_pos->x;
        int map_y = (int)mem->player_pos->y;

        // 3. Calculate distance to next x or y side
        double delta_dist_x = fabs(1.0 / ray_dir_x);
        double delta_dist_y = fabs(1.0 / ray_dir_y);

        // 4. Calculate step and initial side_dist
        int step_x;
        int step_y;
        double side_dist_x;
        double side_dist_y;

        // Calculate step direction and initial side distance for X
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (mem->player_pos->x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - mem->player_pos->x) * delta_dist_x;
        }

        // Calculate step direction and initial side distance for Y
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (mem->player_pos->y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - mem->player_pos->y) * delta_dist_y;
        }

        // 5. Perform DDA
        int hit = 0;
        int side; // 0 for x-side, 1 for y-side

        while (hit == 0)
        {
            // Jump to next map square
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            // Check if ray has hit a wall
            if (map_x < 0 || map_x >= mem->resources->map_width ||
                map_y < 0 || map_y >= (mem->resources->map_height - mem->map_start_row))
                break;  // Ray is out of bounds
            
            if (mem->map[map_y][map_x] == '1')
                hit = 1;
	 	}

        // Debug output
        if (hit)
        {
            printf("\nWall hit at coordinates: x=%d, y=%d\n", map_x, map_y);
            printf("Ray direction: x=%f, y=%f\n", ray_dir_x, ray_dir_y);
            if (side == 0)
                printf("Hit vertical wall\n");
            else
                printf("Hit horizontal wall\n");
        }

        // Store the hit position
        ray->ray_x = map_x;
        ray->ray_y = map_y;
	}
    
		// if (ray_num == 320)
		// {
		// 	printf("\n");
		// 	//x direction
		// 	printf("player angle %f\n", mem->player_pos->angle/M_PI);
		// 	//edgecase of straight no intersect in map bounds
			
		// 	// normalized direction for increments
		// 	int direction_x = (cos(ray->angle) > 0) ? 1 : -1;
		// 	printf("direction_x: %d\n", direction_x);
		// 	int direction_y = (sin(ray->angle) > 0) ? 1 : -1;
		// 	printf("direction_y: %d\n", direction_y);

		// 	//initial step x
		// 	if (direction_x < 0)
		// 		ray->step_x = (ray->ray_x - (int)(ray->ray_x)) * direction_x;
		// 	else if (direction_x > 0)
		// 	    ray->step_x = (int)(ray->ray_x + 1) - ray->ray_x;
		// 	else
		// 		ray->step_x = 0;
		// 	printf("step_x: %f\n", ray->step_x);
		// 	// printf("tan: %f\n", tan(ray->angle));
		// 	//initial step y
		// 	ray->step_y += ray->step_x * sin(ray->angle);
		// 	// if (ray->step_y > mem->player_pos->y -)
		// 	// 	ray->step_y = -ray->step_y;
		// 	printf("step_y: %f\n", ray->step_y);
		// 	ray->ray_x += ray->step_x;
		// 	ray->ray_y += ray->step_y;

		// 	if (ray->ray_y < 0)
		// 		ray->ray_y = 0;
		// 	if (ray->ray_y >= get_memory()->resources->map_height - get_memory()->map_start_row)
		// 		ray->ray_y = get_memory()->resources->map_height - get_memory()->map_start_row - 1;
		// 	// dist_x_step = (ray->ray_y - mem->player_pos->y) / sin(ray->angle);
		// 	// printf("dist_x_step: %f\n", dist_x_step);
		// 	printf("player coords x: %f, y: %f\n", mem->player_pos->x, mem->player_pos->y);
		// 	// printf("intersextion x: %f, y: %f is: %c\n", ray->ray_x, ray->ray_y, mem->map[(int)ray->ray_y][(int)ray->ray_x]);
		// 	while (ray->ray_x >= 0 && ray->ray_x < mem->resources->map_width
		// 		&& ray->ray_y >= 0 && ray->ray_y < mem->resources->map_height - get_memory()->map_start_row
		// 		&& mem->map[(int)ray->ray_y][(int)ray->ray_x] != '1')
		// 	{
		// 		ray->ray_x += direction_x;
		// 		ray->ray_y += sin(ray->angle);
		// 		if (ray->ray_y < 0)
		// 			ray->ray_y = 0;
		// 		if (ray->ray_y >= get_memory()->resources->map_height - get_memory()->map_start_row)
		// 			ray->ray_y = get_memory()->resources->map_height - get_memory()->map_start_row - 1;
		// 	}
		// 	if (mem->map[(int)ray->ray_y][(int)ray->ray_x])
		// 	{
		// 		printf("sin: %f\n", sin(ray->angle));	
		// 		printf("wall hit-> x: %d y: %d\n", (int)ray->ray_x, (int)ray->ray_y);
				
		// 	}

		// }
	
		ray->ray_x = mem->player_pos->x;
		ray->ray_y = mem->player_pos->y;
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
						ray->tex_x = (int)(1 - (ray->ray_y - (int)ray->ray_y) * mem->mlx_data->tex_width);
					}
					else if ((int)ray->ray_y > ray->last_y)
					{
						ray->tex_num = NORTH;
						ray->tex_x = (int)(1 - (ray->ray_x - (int)ray->ray_x) * mem->mlx_data->tex_width);
					}
					else if ((int)ray->ray_y < ray->last_y)
					{
						ray->tex_num = SOUTH;
						ray->tex_x = (int)((ray->ray_x - (int)ray->ray_x) * mem->mlx_data->tex_width);
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



// void		cast_rays()
// {
// 	t_memory	*mem;
// 	t_ray		*ray;
// 	int			ray_num;
// 	double		angle_per_pixel;
	
// 	ray = malloc(sizeof(t_ray));
// 	ray_num = 0;
// 	mem = get_memory();
// 	angle_per_pixel = M_PI/3 / mem->mlx_data->resolution_x;
// 	ray->angle = mem->player_pos->angle - M_PI/6;		
// 	while (ray_num < mem->mlx_data->resolution_x)
// 	{
// 		ray->ray_x = mem->player_pos->x;
// 		ray->ray_y = mem->player_pos->y;
// 		ray->step_x = cos(ray->angle) / 1000;
// 		ray->step_y = sin(ray->angle) / 1000;
// 		while (ray->ray_x > 0 && ray->ray_x < mem->resources->map_width
// 			&& ray->ray_y > 0 && ray->ray_y < mem->resources->map_height
// 			&& mem->map[(int)ray->ray_y][(int)ray->ray_x] != '1')
// 		{
// 			ray->last_x = (int)ray->ray_x;
// 			ray->last_y = (int)ray->ray_y;
// 			ray->ray_x += ray->step_x;
// 			ray->ray_y += ray->step_y;
// 			if ((int)ray->ray_x != ray->last_x || (int)ray->ray_y != ray->last_y)
// 			{
// 				if (mem->map[(int)ray->ray_y][(int)ray->ray_x] == '1')
// 				{
// 					if((int)ray->ray_x > ray->last_x)
// 					{
// 						ray->tex_num = WEST;
// 						ray->tex_x = (int)((ray->ray_y - (int)ray->ray_y) * mem->mlx_data->tex_width);
// 					}
// 					else if ((int)ray->ray_x < ray->last_x)
// 					{
// 						ray->tex_num = EAST;
// 						ray->tex_x = (int)(1 - (ray->ray_y - (int)ray->ray_y) * mem->mlx_data->tex_width);
// 					}
// 					else if ((int)ray->ray_y > ray->last_y)
// 					{
// 						ray->tex_num = NORTH;
// 						ray->tex_x = (int)(1 - (ray->ray_x - (int)ray->ray_x) * mem->mlx_data->tex_width);
// 					}
// 					else if ((int)ray->ray_y < ray->last_y)
// 					{
// 						ray->tex_num = SOUTH;
// 						ray->tex_x = (int)((ray->ray_x - (int)ray->ray_x) * mem->mlx_data->tex_width);
// 					}
// 					double distance = sqrt((ray->ray_x - mem->player_pos->x) * (ray->ray_x - mem->player_pos->x)
// 										+ (ray->ray_y - mem->player_pos->y) * (ray->ray_y - mem->player_pos->y));
// 					ray->line_height = mem->mlx_data->resolution_y / (distance * cos(ray->angle - mem->player_pos->angle));
// 					ray->draw_start = -ray->line_height / 2 + mem->mlx_data->resolution_y / 2;
// 					ray->draw_end = ray->line_height / 2 + mem->mlx_data->resolution_y / 2;
// 					t_texture tex = mem->mlx_data->textures[ray->tex_num];
// 					int y = 0;
// 					while (y < mem->mlx_data->resolution_y)
// 					{
// 						if(y < ray->draw_start)
// 						{
// 							my_mlx_pixel_put(ray_num, y, mem->resources->ceiling_color);
// 						}
// 						else if (y > ray->draw_end)
// 						{
// 							my_mlx_pixel_put(ray_num, y, mem->resources->floor_color);
// 						}
// 						else
// 						{
// 							int tex_y = (int)((y - ray->draw_start) * (double)512 / (ray->draw_end - ray->draw_start));
// 							tex_y = (tex_y < 0) ? 0 : tex_y;
// 							tex_y = (tex_y >= 512) ? 512 - 1 : tex_y;
// 							unsigned int color = *(unsigned int*)(tex.addr + (tex_y * tex.line_length + ray->tex_x * (tex.bpp / 8)));
// 								my_mlx_pixel_put(ray_num, y, color);
// 						}
// 						y++;
// 					} 
// 					break;
// 				}
// 			}
// 		}
// 		ray_num++;
// 		ray->angle += angle_per_pixel;
// 	}
// 	free(ray);
// }
