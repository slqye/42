/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:12:48 by slaye             #+#    #+#             */
/*   Updated: 2024/06/25 12:40:56 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	vertical_right(t_player *player, t_ray *ray)
{
	if (ray->dist == 0)
	{
		ray->cx = ceil(player->x) - player->x + OFFSET;
		ray->cy = ray->cx * tan(player->rayrot);
		ray->dist += sqrt(ray->cy * ray->cy + ray->cx * ray->cx);
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
	else
	{
		ray->cx += SCELL;
		ray->cy += SCELL * tan(player->rayrot);
		ray->dist += sqrt(SCELL + (SCELL * tan(player->rayrot)) \
		* (SCELL * tan(player->rayrot)));
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
}

void	vertical_left(t_player *player, t_ray *ray)
{
	if (ray->dist == 0)
	{
		ray->cx = -(player->x - floor(player->x) + OFFSET);
		ray->cy = ray->cx * tan(player->rayrot);
		ray->dist += sqrt(ray->cy * ray->cy + ray->cx * ray->cx);
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
	else
	{
		ray->cx += -SCELL;
		ray->cy += -SCELL * tan(player->rayrot);
		ray->dist += sqrt(SCELL + (-SCELL * tan(player->rayrot)) \
		* (-SCELL * tan(player->rayrot)));
		ray->py = floor(player->y - ray->cy);
		ray->px = floor(player->x + ray->cx);
	}
}

double	get_vertical(t_program *program)
{
	t_player	*player;
	t_ray		ray;

	player = program->player;
	ray.px = floor(player->x);
	ray.py = floor(player->y);
	ray.dist = 0;
	if (player->rayrot == PI / 2 || player->rayrot == -PI / 2)
		return (99999999);
	while (is_in_map(program->map->grid, ray.py, ray.px) \
	&& program->map->grid[(int) ray.py][(int) ray.px] != WALL)
	{
		if (player->rayrot < PI / 2 || player->rayrot > 3 * PI / 2)
			vertical_right(player, &ray);
		else
			vertical_left(player, &ray);
	}
	return (ray.dist);
}
