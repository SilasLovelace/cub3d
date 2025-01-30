/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:26:36 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/30 14:45:09 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FUNCTIONS_H
# define	FUNCTIONS_H

#include "structs.h"

// freeing/freeing.c
void	free_memory(void);

//test_tools/print_states.c
void   print_memory(void);

// map_tools
    //map_parser.c

int is_valid_map_name (char* map_name);
int is_valid_resource(char* line);
int is_valid_map(char** line);

    //file_reader.c
char    **read_file_lines(const char *filename);

//main.c
t_memory    *get_memory(void);

//game/run_game.c
void	run_game(void);

//display/display.c
void	display(void);

//close/close_game.c
int close_game(void);
int close_game_error(void);
void	destroy(t_memory *memory);

//raycaster/raycaster.c
void    get_texture_dimensions(char *filepath);

#endif