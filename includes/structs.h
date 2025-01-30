/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:37:19 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/30 14:24:11 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		STRUCTS_H
# define		STRUCTS_H

typedef struct s_map_resources
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		ceiling_color;
	int		floor_color;
}   t_map_resources;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	v_x;
	float	v_y;
}	t_coordinates;

typedef struct s_mlx_data
{
    void    *mlx;            
    void    *window;          
    void    *img;             
    char    *addr;            
    int     bpp;              
    int     line_length;      
    int     endian;           
    int     resolution_x;     
    int     resolution_y;
	 
    void    *north_texture;   
    void    *south_texture;  
    void    *east_texture;   
    void    *west_texture;   
	
    int     tex_width;       
    int     tex_height;      
} t_mlx_data;

typedef struct s_memory
{
	t_mlx_data		*mlx_data;
	t_map_resources	*resources;
	char			**map;
	t_coordinates	*player_pos;
	int				map_start_row;
}	t_memory;

#endif