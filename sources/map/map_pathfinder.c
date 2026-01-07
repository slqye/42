/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:33:18 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/09 17:56:30 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"

int	expender_callback(char **data_clone, int y, int x)
{
	return (data_clone[y][x] = '+', 1);
}

int	expender_adder(t_map *map, char **data_clone, int x, int y)
{
	int	result;

	result = 0;
	if (y > 0 && (data_clone[y - 1][x] == '0' \
	|| data_clone[y - 1][x] == 'C' || data_clone[y - 1][x] == 'E'))
		result = expender_callback(data_clone, y - 1, x);
	if (y < map->size.y && (data_clone[y + 1][x] == '0' \
	|| data_clone[y + 1][x] == 'C' || data_clone[y + 1][x] == 'E'))
		result = expender_callback(data_clone, y + 1, x);
	if (x > 0 && (data_clone[y][x - 1] == '0' \
	|| data_clone[y][x - 1] == 'C' || data_clone[y][x - 1] == 'E'))
		result = expender_callback(data_clone, y, x - 1);
	if (x < map->size.x && (data_clone[y][x + 1] == '0' \
	|| data_clone[y][x + 1] == 'C' || data_clone[y][x + 1] == 'E'))
		result = expender_callback(data_clone, y, x + 1);
	return (result);
}

void	expender(t_map *map, char **data_clone, int x, int y)
{
	t_vector2	coords;
	int			i;

	i = expender_adder(map, data_clone, x, y);
	if (i == 0)
		return ;
	coords.y = 0;
	while (coords.y < map->size.y)
	{
		coords.x = 0;
		while (coords.x < map->size.x)
		{
			if (data_clone[coords.y][coords.x] == PATHFINDER)
				expender(map, data_clone, coords.x, coords.y);
			coords.x++;
		}
		coords.y++;
	}
}

char	**data_cloner(t_map *map)
{
	int		i;
	char	**result;

	i = 0;
	result = malloc(sizeof(char *) * (map->size.y + 1));
	if (result == NULL)
		return (NULL);
	while (i <= map->size.y)
	{
		result[i] = ft_strdup(map->data[i]);
		if (result[i] == NULL)
			return (freetab(result, i), NULL);
		i++;
	}
	return (result);
}

char	**pathfinder(t_map *map, t_vector2 player)
{
	char		**data_clone;

	data_clone = data_cloner(map);
	if (data_clone == NULL)
		return (NULL);
	expender(map, data_clone, player.x, player.y);
	return (data_clone);
}
