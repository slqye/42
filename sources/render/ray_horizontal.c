/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:12:48 by slaye             #+#    #+#             */
/*   Updated: 2024/06/27 14:51:11 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	horizontal_upper(t_player *player, t_ray *ray)
{
	if (ray->dist == 0)
	{
		ray->cy = player->y - floor(player->y) + OFFSET;
		ray->cx = ray->cy / tan(player->rayrot);
		ray->dist += sqrt(ray->cy * ray->cy + ray->cx * ray->cx);
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
	else
	{
		ray->cy += SCELL;
		ray->cx += SCELL / tan(player->rayrot);
		ray->dist += sqrt(SCELL + (SCELL / tan(player->rayrot)) \
		* (SCELL / tan(player->rayrot)));
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
}

void	horizontal_lower(t_player *player, t_ray *ray)
{
	if (ray->dist == 0)
	{
		ray->cy = -(ceil(player->y) - player->y + OFFSET);
		ray->cx = ray->cy / tan(player->rayrot);
		ray->dist += sqrt(ray->cy * ray->cy + ray->cx * ray->cx);
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
	else
	{
		ray->cy += -SCELL;
		ray->cx += -SCELL / tan(player->rayrot);
		ray->dist += sqrt(SCELL + (-SCELL / tan(player->rayrot)) \
		* (-SCELL / tan(player->rayrot)));
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
}

double	get_horizontal(t_program *program)
{
	t_player	*player;
	t_ray		ray;

	player = program->player;
	ray.px = floor(player->x);
	ray.py = floor(player->y);
	ray.dist = 0;
	if (player->rayrot == 0 || player->rayrot == PI)
		return (99999999);
	while (is_in_map(program->map->grid, ray.py, ray.px) \
	&& program->map->grid[(int) ray.py][(int) ray.px] != WALL)
	{
		if (player->rayrot < PI)
			horizontal_upper(player, &ray);
		else
			horizontal_lower(player, &ray);
	}
	player->rayoffset = ceil(ray.cx) - ray.cx;
	return (ray.dist);
}
