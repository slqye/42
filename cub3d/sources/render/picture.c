/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-lang <mde-lang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:31:52 by mde-lang          #+#    #+#             */
/*   Updated: 2024/06/28 12:10:07 by mde-lang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	is_in_tex(uint32_t y, uint32_t x)
{
	if (y >= W_HEIGHT)
		return (0);
	else if (x >= W_WIDTH)
		return (0);
	return (1);
}

void	set_line_dist(t_raycaster *rc, t_line *line, int type)
{
	if (type == 0)
		line->distance = rc->horizontal;
	else
		line->distance = rc->vertical;
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	fc_printer_subpart(t_program *program, char **ceiling, char **floor)
{
	int	y;
	int	x;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_HEIGHT / 2)
			mlx_put_pixel(program->screen, y, x, ft_pixel(ft_atoi(ceiling[0]),
					ft_atoi(ceiling[1]), ft_atoi(ceiling[2]), 255));
		while (++x < W_HEIGHT)
			mlx_put_pixel(program->screen, y, x, ft_pixel(ft_atoi(floor[0]),
					ft_atoi(floor[1]), ft_atoi(floor[2]), 255));
		y++;
	}
}

void	fc_printer(t_program *program)
{
	char	**ceiling;
	char	**floor;

	ceiling = ft_split(program->map->c, ',');
	if (!ceiling)
		fexit(program, EXIT_FAILURE, ER_MALLOC, STDERR_FILENO);
	floor = ft_split(program->map->f, ',');
	if (!floor)
	{
		free_split(ceiling);
		fexit(program, EXIT_FAILURE, ER_MALLOC, STDERR_FILENO);
	}
	fc_printer_subpart(program, ceiling, floor);
	free_split(ceiling);
	free_split(floor);
}
