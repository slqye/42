/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:38:39 by slaye             #+#    #+#             */
/*   Updated: 2024/06/27 16:10:51 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	is_in_screen(int x, int y)
{
	if (x < W_WIDTH && x >= W_WIDTH / 2 && y >= 0 && y < W_HEIGHT)
		return (1);
	return (0);
}

double	a_normalize(double angle)
{
	double	result;

	result = angle;
	if (result < 0)
		result += (2 * PI);
	if (result > (2 * PI))
		result -= (2 * PI);
	return (result);
}

unsigned int	get_pixel_color(uint8_t *pixels, int width, int x, int y)
{
	int	index;

	index = (y * width + x) * 4;
	return (ft_pixel(pixels[index], pixels[index + 1], \
	pixels[index + 2], pixels[index + 3]));
}

int	loop_line_horizontal(t_program *program, t_line line, mlx_texture_t *tex)
{
	if (line.type == 0 && program->player->rayrot < PI)
	{
		if (is_in_screen(line.step, line.i))
		{
			mlx_put_pixel(program->screen, line.step, line.i, \
			get_pixel_color(tex->pixels, tex->width, line.p1 * tex->width, \
			line.j * tex->width / (W_HEIGHT / line.distance)));
			return (1);
		}
	}
	else if (line.type == 0 && program->player->rayrot > PI)
	{
		if (is_in_screen(line.step, line.i))
		{
			mlx_put_pixel(program->screen, line.step, line.i, \
			get_pixel_color(tex->pixels, tex->width, \
			fabs(line.p1 - 1.0) * tex->width, \
			line.j * tex->width / (W_HEIGHT / line.distance)));
			return (1);
		}
	}
	return (0);
}

void	loop_line_vertical(t_program *program, t_line line, mlx_texture_t *tex)
{
	if (line.type != 0 && (program->player->rayrot < PI / 2 \
	|| program->player->rayrot > 3 * PI / 2) \
	&& is_in_tex(line.p2 * tex->width, line.j * tex->width / line.l))
	{
		if (is_in_screen(line.step, line.i))
		{
			mlx_put_pixel(program->screen, line.step, line.i, \
			get_pixel_color(tex->pixels, tex->width, line.p2 * tex->width, \
			line.j * tex->width / (W_HEIGHT / line.distance)));
		}
	}
	else if (is_in_screen(line.step, line.i))
	{
		mlx_put_pixel(program->screen, line.step, line.i, \
		get_pixel_color(tex->pixels, tex->width, \
		fabs(line.p2 - 1) * tex->width, \
		line.j * tex->width / (W_HEIGHT / line.distance)));
	}
}
