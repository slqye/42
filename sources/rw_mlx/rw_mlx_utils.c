/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:38:31 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/13 17:37:19 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"
#include "../../includes/rw_mlx.h"
#include "../../includes/player.h"

int	on_destroy(t_program *program)
{
	clear_window_image(*program);
	mlx_destroy_window(program->mlx, program->window);
	mlx_destroy_display(program->mlx);
	mlx_loop_end(program->mlx);
	free(program->mlx);
	freetab(program->map->data, program->map->size.y);
	free(program->map);
	free(program->textures);
	exit(0);
	return (0);
}

int	on_keyinput(int keycode, t_program *program)
{
	t_vector2	coords;

	if (keycode == KEYCODE_ESC)
		return (on_destroy(program));
	else
	{
		coords = get_coords(program->map, PLAYER);
		if (keycode == KEYCODE_W)
			move_up(program, coords);
		if (keycode == KEYCODE_A)
			move_left(program, coords);
		if (keycode == KEYCODE_S)
			move_down(program, coords);
		if (keycode == KEYCODE_D)
			move_right(program, coords);
		show_map(*program);
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
