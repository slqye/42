/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:52:49 by mde-lang          #+#    #+#             */
/*   Updated: 2024/06/27 15:47:55 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	minimap_resize(t_map *map)
{
	while ((ft_lstsize(map->lst_grid) * SQUARE) * map->ratio_y > (W_HEIGHT))
		map->ratio_y -= 0.001;
	while ((max_len_map(map->grid) * SQUARE) * map->ratio_x > (W_WIDTH / 2))
		map->ratio_x -= 0.001;
	while ((ft_lstsize(map->lst_grid) * SQUARE) * map->ratio_y < (W_HEIGHT))
		map->ratio_y += 0.001;
	while ((max_len_map(map->grid) * SQUARE) * map->ratio_x < (W_WIDTH / 2))
		map->ratio_x += 0.001;
}

int	max_len_map(char **grid)
{
	int	y;
	int	tmp;
	int	len;

	y = 0;
	tmp = 0;
	len = 0;
	while (grid[y])
	{
		tmp = ft_strlen(grid[y]);
		if (tmp > len)
			len = tmp;
		y++;
	}
	return (len);
}

void	draw_square(t_program *p, int x, int y, uint32_t color)
{
	double	yy;
	double	xx;
	int		holder;

	yy = y + SQUARE * p->map->ratio_y;
	xx = x + SQUARE * p->map->ratio_x;
	holder = x;
	while (y < yy && y < W_HEIGHT)
	{
		x = holder;
		while (x < xx && x < W_WIDTH / 2)
			mlx_put_pixel(p->minimap, x++, y, color);
		y++;
	}
}

void	draw_map(t_program *p)
{
	int	x;
	int	y;

	y = 0;
	minimap_resize(p->map);
	while (y < ft_lstsize(p->map->lst_grid))
	{
		x = 0;
		while (x < (int)ft_strlen(p->map->grid[y]))
		{
			if (p->map->grid[y][x] == '1')
				draw_square(p, x * SQUARE * p->map->ratio_x, y
					* SQUARE * p->map->ratio_y, 0xFFFFFFFF);
			else if (p->map->grid[y][x] != '1' && p->map->grid[y][x] != ' ')
				draw_square(p, x * SQUARE * p->map->ratio_x, y
					* SQUARE * p->map->ratio_y, 0x000000FF);
			x++;
		}
		y++;
	}
}
