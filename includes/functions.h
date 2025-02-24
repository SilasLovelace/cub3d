/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:26:36 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/20 10:01:22 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

//init/init.c
t_memory	*get_memory(void);

//freeing/freeing.c
void		free_memory(void);

//map_tools/utils.c
char		*find_next_comma(char *str);
char		*skip_whitespace(char *str);
char		*skip_non_whitespace(char *str);
void		set_player_coordinates(char orientation, int x, int y);

//map_tools/validation.c
int			is_valid_map(char **map);

//map_tools/validation_utils.c
int			is_valid_resource(char *line);

//map_tools/create_map.c
void		create_map(void);

//map_tools/map_parser.c
int			parse_map(char **av);

//map_tools/get_data.c
char		**get_resource_dest(char *identifier);
int			*get_color_dest(char *identifier);

//map_tools/file_reader.c
char		**read_file_lines(const char *filename);

//game/run_game.c
void		run_game(void);

//game/handlers.c
int			handle_keypress(int key, t_memory *memory);
int			handle_keyrelease(int key, t_memory *memory);

//game/moving.c
void		move_forward(void);
void		move_backward(void);
void		move_left(void);
void		move_right(void);

//game/images.c
void		take_images(void);

//game/rotation.c
void		rotate_left(void);
void		rotate_right(void);

//display/display.c
void		display(void);
void		my_mlx_pixel_put(int x, int y, int color);

//close/close_game.c
int			close_game(void);
int			close_game_error(void);
void		destroy(t_memory *memory);

//raycaster/raycaster.c
void		cast_rays(void);

//raycaster/raycaster_utils .c
void		reset_ray_params(t_ray *ray, int parse_density);
int			is_inbound(t_ray *ray);
void		increment_step(t_ray *ray);
int			get_mlx_img_pixel_color(t_texture *tex, int x, int y);

#endif