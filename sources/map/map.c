/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:58:11 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/15 18:06:15 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"
#include "../../includes/rw_mlx.h"

t_vector2	get_coords(t_map *map, char c)
{
	t_vector2	result;

	result.y = -1;
	while (++result.y < map->size.y)
	{
		result.x = -1;
		while (++result.x < map->size.x)
		{
			if (map->data[result.y][result.x] == c)
				return (result);
		}
	}
	result.x = -1;
	result.y = -1;
	return (result);
}

int	count_line(char *path)
{
	char	buffer;
	int		result;
	int		reads;
	int		fd;

	fd = open(path, O_RDONLY);
	result = 0;
	reads = -1;
	while (reads == -1 || reads > 0)
	{
		reads = read(fd, &buffer, 1);
		if (reads == -1)
			return (close(fd), result);
		if (buffer == '\n')
			result++;
	}
	return (close(fd), result);
}

int	set_data(int fd, t_map *map, int height)
{
	t_vector2	size;
	int			i;

	i = -1;
	while (++i <= height)
	{
		map->data[i] = get_next_line(fd);
		if (map->data[i] == NULL)
			return (freetab(map->data, i), 0);
		else if (i == 0)
			size.x = ft_strlen(map->data[0]);
	}
	size.y = height;
	map->size = size;
	return (1);
}

t_map	*get_map(char *path)
{
	t_map		*map;
	int			fd;
	int			height;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (close(fd), NULL);
	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (close(fd), NULL);
	height = count_line(path);
	map->data = malloc(sizeof(char *) * (height + 1));
	if (map->data == NULL)
		return (free(map), NULL);
	if (!set_data(fd, map, height))
		return (free(map), NULL);
	close(fd);
	if (check_map(map) == 1)
		return (freetab(map->data, map->size.y), free(map), NULL);
	return (map);
}
