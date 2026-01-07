/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:10:38 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/13 17:58:10 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"
#include "../../includes/rw_mlx.h"

int	check_custom_map_char(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			if (map->data[y][x] != WALL && map->data[y][x] != FLOOR)
			{
				if (map->data[y][x] != COLLECT && map->data[y][x] != PLAYER)
				{
					if (map->data[y][x] != EXIT && map->data[y][x] != SKEL)
						return (0);
				}
			}
		}
	}
	return (1);
}
