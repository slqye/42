/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:11:14 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/13 16:28:20 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

int	get_map_char(t_map *map, char c)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			if (map->data[y][x] == c)
				count++;
		}
	}
	return (count);
}

int	is_map_rectangular(t_map *map)
{
	int	i;

	i = 0;
	while (i + 1 <= map->size.y)
	{
		if (ft_strlen(map->data[i]) != ft_strlen(map->data[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	is_line_walled(char *line)
{
	int	i;

	i = 1;
	while (i < (int) ft_strlen(line) - 1)
	{
		if (line[i] != WALL)
			return (0);
		i++;
	}
	return (1);
}

int	is_map_close(t_map *map)
{
	char	**data;
	int		i;

	i = -1;
	while (++i <= map->size.y)
	{
		data = map->data;
		if (i == 0 || i == map->size.y)
		{
			if (ft_strlen(data[i]) <= 2)
				return (0);
			if (!is_line_walled(data[i]))
				return (0);
		}
		else if (data[i][0] != WALL || data[i][ft_strlen(data[i]) - 1] != WALL)
			return (0);
		else if (data[i][ft_strlen(data[i]) - 1] != WALL)
			return (0);
	}
	return (1);
}

int	check_map(t_map *map)
{
	int		error;

	error = 0;
	if (!check_custom_map_char(map))
		error = 1;
	else if (get_map_char(map, PLAYER) != 1 || get_map_char(map, EXIT) != 1)
		error = 1;
	else if (get_map_char(map, COLLECT) < 1)
		error = 1;
	else if (!is_map_rectangular(map))
		error = 1;
	else if (!is_map_close(map))
		error = 1;
	else if (!is_map_valid_path(map, pathfinder(map, get_coords(map, PLAYER))))
		error = 1;
	return (error);
}
