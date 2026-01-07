/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:25:21 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/09 17:00:01 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

int	is_map_valid_path(t_map *map, char **pathfinder)
{
	t_vector2	coords;

	coords.y = -1;
	if (pathfinder == NULL)
		return (0);
	while (++coords.y <= map->size.y)
	{
		coords.x = -1;
		while (++coords.x < map->size.x)
		{
			if (map->data[coords.y][coords.x] == COLLECT)
			{
				if (pathfinder[coords.y][coords.x] != PATHFINDER)
					return (freetab(pathfinder, map->size.y), 0);
			}
			if (map->data[coords.y][coords.x] == EXIT)
			{
				if (pathfinder[coords.y][coords.x] != PATHFINDER)
					return (freetab(pathfinder, map->size.y), 0);
			}
		}
	}
	return (freetab(pathfinder, map->size.y), 1);
}
