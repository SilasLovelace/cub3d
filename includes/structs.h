/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:37:19 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/17 14:45:43 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	int		last_x;
	int		last_y;
	double	step_x;
	double	step_y;
	double	angle;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
}	t_ray;

typedef struct s_map_resources
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		ceiling_color;
	int		floor_color;
	int		map_width;
	int		map_height;
}	t_map_resources;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	angle;
}	t_coordinates;

typedef struct s_keys
{
	int	w_pressed;
	int	s_pressed;
	int	a_pressed;
	int	d_pressed;
	int	left_pressed;
	int	right_pressed;
}	t_keys;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			resolution_x;
	int			resolution_y;
	int			fov;
	t_texture	textures[4];
	int			tex_width;
	int			tex_height;
}	t_mlx_data;

typedef struct s_memory
{
	t_mlx_data		*mlx_data;
	t_map_resources	*resources;
	char			**input;
	char			**map;
	t_coordinates	*player_pos;
	int				map_start_row;
	t_keys			*keys;
}	t_memory;

#endif