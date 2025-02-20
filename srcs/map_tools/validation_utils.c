/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:46:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/19 17:34:02 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_number(char *str, char term)
{
	int		i;
	char	*start;

	i = 0;
	start = str;
	while (*str && ft_isdigit(*str))
	{
		str++;
		i++;
	}
	if (i > 3 || i == 0 || (*str != term && *str != '\n')
		|| ft_atoi(start) > 255)
		return (-1);
	return (i);
}

static int	is_valid_rgb(char *str)
{
	int	color;

	if (parse_number(str, ',') >= 0)
	{
		color = ft_atoi(str) * 256 * 256;
		str += parse_number(str, ',') + 1;
	}
	else
		return (-1);
	if (parse_number(str, ',') >= 0)
	{
		color += ft_atoi(str) * 256 ;
		str += parse_number(str, ',') + 1;
	}
	else
		return (-1);
	if (parse_number(str, ' ') >= 0)
		color += ft_atoi(str);
	else
		return (-1);
	return (color);
}

static int	check_textures(char *begin_info, char *first_non_ws)
{
	char	*end_info;

	if (!ft_strncmp(begin_info, "./", 2) && *(begin_info + 2) != ' ')
	{
		end_info = skip_non_whitespace(begin_info + 2);
		if (!(*(end_info) == '\0' || *skip_whitespace(end_info) == '\n')
			|| !get_resource_dest(first_non_ws))
			return (0);
		if (*(end_info - 1) == '\n')
			end_info--;
		*(char**)get_resource_dest(first_non_ws) \
			= ft_substr(begin_info, 0, end_info - begin_info);
		return (1);
	}
	return (0);
}

static int	check_colors(char *begin_info, char *first_non_ws)
{
	char	*end_info;

	if (is_valid_rgb(begin_info) >= 0)
	{
		end_info = skip_non_whitespace(begin_info);
		if (!(*(end_info) == '\0' || *skip_whitespace(end_info) == '\n')
			|| !get_color_dest(first_non_ws))
			return (0);
		*get_color_dest(first_non_ws) = is_valid_rgb(begin_info);
		return (1);
	}
	return (0);
}

int	is_valid_resource(char *line)
{
	char	*first_non_ws;
	char	*begin_info;

	first_non_ws = skip_whitespace(line);
	if (!ft_strncmp(first_non_ws, "NO ", 3)
		|| !ft_strncmp(first_non_ws, "SO ", 3)
		|| !ft_strncmp(first_non_ws, "WE ", 3)
		|| !ft_strncmp(first_non_ws, "EA ", 3))
	{
		begin_info = skip_whitespace(first_non_ws + 2);
		return (check_textures(begin_info, first_non_ws));
	}
	else if (!ft_strncmp(first_non_ws, "C ", 2)
		|| !ft_strncmp(first_non_ws, "F ", 2))
	{
		begin_info = skip_whitespace(first_non_ws + 1);
		return (check_colors(begin_info, first_non_ws));
	}
	else
		return (0);
}
