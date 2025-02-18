/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:37:09 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/18 18:09:05 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_lines(int fd)
{
	bool	flag;
	int		counter;
	char	*line;

	flag = false;
	counter = 0;
	while (1)
	{
		line = get_next_line(fd, &flag, false);
		if (flag)
		{
			printf("Error! Memory allocation failed\n");
			free_memory();
			exit(1);
		}
		if (!line)
			break ;
		counter++;
		free(line);
	}
	return (counter);
}

static bool	read_lines_into_array(int fd, char **lines, int line_count)
{
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	while (i < line_count)
	{
		lines[i] = get_next_line(fd, &flag, false);
		if (flag)
		{
			printf("Error! Memory allocation failed\n");
			while (--i >= 0)
				free(lines[i]);
			return (free(lines), close(fd), false);
		}
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			return (free(lines), close(fd), false);
		}
		i++;
	}
	lines[i] = NULL;
	return (true);
}

char	**read_file_lines(const char *filename)
{
	int		fd;
	char	**lines;
	int		line_count;
	bool	flag;

	flag = false;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_count = count_lines(fd);
	close(fd);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	if (!read_lines_into_array(fd, lines, line_count))
		return (NULL);
	close(fd);
	return (lines);
}
