/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:41:32 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/17 12:30:15 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(int x, int y, int color)
{
	t_memory	*memory;
	char		*dst;

	memory = get_memory();
	dst = memory->mlx_data->addr + \
		(y * memory->mlx_data->line_length + x * (memory->mlx_data->bpp / 8));
	*(unsigned int *)dst = color;
}

// void	display_background(void)
// {
// 	t_memory	*memory;
// 	int			x;
// 	int			y;

// 	memory = get_memory();
// 	y = 0;
// 	while (y < memory->mlx_data->resolution_y)
// 	{
// 		x = 0;
// 		while (x < memory->mlx_data->resolution_x)
// 		{
// 			if (y < memory->mlx_data->resolution_y / 2)
// 				my_mlx_pixel_put(x, y, memory->resources->ceiling_color);
// 			else
// 				my_mlx_pixel_put(x, y, memory->resources->floor_color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(memory->mlx_data->mlx, memory->mlx_data->window, \
// 		memory->mlx_data->img, 0, 0);
// }

void calculate_map_dimensions(void)
{
	t_memory *memory = get_memory();
	int max_width = 0;
	int height = 0;

	while (memory->input[height])
	{
		int current_width = ft_strlen(memory->input[height]);
		if (current_width > max_width)
			max_width = current_width;
		height++;
	}
		
	memory->resources->map_width = max_width;
	memory->resources->map_height = height;
}

void draw_player_direction(int player_x, int player_y)
{
	t_memory *memory = get_memory();
	int line_length = 8;
	int dir_x = player_x + (memory->player_pos->dir_x * line_length);
	int dir_y = player_y + (memory->player_pos->dir_y * line_length);
	int dx = dir_x - player_x;
	int dy = dir_y - player_y;
	int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	float x_inc = (float)dx / steps;
	float y_inc = (float)dy / steps;
	float x = player_x;
	float y = player_y;

	for (int i = 0; i < steps; i++)
	{
		if (x >= 0 && x < 100 && y >= 0 && y < 100)
			my_mlx_pixel_put(x, y, 0xFF0000);
		x += x_inc;
		y += y_inc;
	}
}

void draw_minimap(void)
{
	t_memory *memory = get_memory();
	int minimap_size = 100;
	int tile_size;
	int border = 10;
	
	if (memory->resources->map_width == 0 || memory->resources->map_height == 0)
		calculate_map_dimensions();
	tile_size = (minimap_size - 2 * border) / 
		(memory->resources->map_width > memory->resources->map_height ? 
			memory->resources->map_width : memory->resources->map_height);
	for (int y = 0; y < minimap_size; y++)
	{
		for (int x = 0; x < minimap_size; x++)
		{
			my_mlx_pixel_put(x, y, 0x222222);
		}
	}
	for (int y = 0; y < memory->resources->map_height; y++)
	{
		for (int x = 0; x < (int)ft_strlen(memory->map[y]); x++)
		{
			int screen_x = border + x * tile_size;
			int screen_y = border + y * tile_size;
			int color;
			if (memory->map[y][x] == '1')
				color = 0xFFFFFF;
			else if (memory->map[y][x] == ' ')
				color = 0x222222;
			else if (ft_strchr("0NSEW", memory->map[y][x]))
				color = 0x444444;
			for (int i = 0; i < tile_size - 1; i++)
			{
				for (int j = 0; j < tile_size - 1; j++)
				{
					if (screen_x + i < minimap_size && screen_y + j < minimap_size)
						my_mlx_pixel_put(screen_x + i, screen_y + j, color);
				}
			}
		}
	}
	int player_x = border + (memory->player_pos->x * tile_size);
	int player_y = border + (memory->player_pos->y * tile_size);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (player_x + i >= 0 && player_x + i < minimap_size &&
				player_y + j >= 0 && player_y + j < minimap_size)
				my_mlx_pixel_put(player_x + i, player_y + j, 0xFF0000);
		}
	}
	draw_player_direction(player_x, player_y);
}

void	display(void)
{
	t_memory	*memory;

	memory = get_memory();

    ft_bzero(memory->mlx_data->addr, 
        memory->mlx_data->resolution_x * memory->mlx_data->resolution_y * 
        (memory->mlx_data->bpp / 8));

	// draw_minimap();
	cast_rays();
	mlx_put_image_to_window(memory->mlx_data->mlx, memory->mlx_data->window, \
		memory->mlx_data->img, 0, 0);
	// printf("Player position: %f, %f\n", memory->player_pos->x, 
	// 	memory->player_pos->y);
	// printf("Player direction: %f, %f\n", memory->player_pos->dir_x, 
	// 	memory->player_pos->dir_y);
}
