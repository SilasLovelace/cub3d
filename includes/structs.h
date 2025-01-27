/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:37:19 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/27 17:42:32 by sopperma         ###   ########.fr       */
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


typedef struct s_memory
{
	t_map_resources	*resources;
	char 		  **map;
}	t_memory;

#endif