/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_mlx_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:17:28 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/15 16:52:53 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map.h"
#include "../../includes/rw_mlx.h"

void	*get_current_image(t_program program, t_vector2 coords)
{
	void	*image;

	image = NULL;
	if (program.map->data[coords.y][coords.x] == WALL)
		image = get_image(program.mlx, TEXTR_WALL).pointer;
	else if (program.map->data[coords.y][coords.x] == FLOOR)
		image = get_image(program.mlx, TEXTR_FLOOR).pointer;
	else if (program.map->data[coords.y][coords.x] == PLAYER)
		image = get_image(program.mlx, program.current_psprite).pointer;
	else if (program.map->data[coords.y][coords.x] == EXIT)
		image = get_image(program.mlx, TEXTR_EXIT).pointer;
	else if (program.map->data[coords.y][coords.x] == COLLECT)
		image = get_image(program.mlx, TEXTR_COLLECT).pointer;
	else if (program.map->data[coords.y][coords.x] == SKEL)
		image = get_image(program.mlx, TEXTR_SKEL).pointer;
	return (image);
}

void	clear_window_image(t_program program)
{
	t_vector2	coords;
	int			i;

	i = 0;
	coords.y = 0;
	while (coords.y <= program.map->size.y)
	{
		coords.x = 0;
		while (coords.x < program.map->size.x)
		{
			if (program.textures[i] != NULL)
				mlx_destroy_image(program.mlx, program.textures[i]);
			coords.x++;
			i++;
		}
		coords.y++;
	}
}

void	put_string(t_program program)
{
	char	*holder;

	holder = ft_itoa(program.movements);
	mlx_string_put(program.mlx, program.window, 10, 20, \
	create_trgb(0, 255, 255, 255), holder);
	if (!holder)
		on_destroy(&program);
	free(holder);
}

void	show_map(t_program program)
{
	t_vector2	coords;
	void		*image;
	int			i;

	i = 0;
	coords.y = -1;
	clear_window_image(program);
	while (++coords.y <= program.map->size.y)
	{
		coords.x = -1;
		while (++coords.x < program.map->size.x)
		{
			image = get_current_image(program, coords);
			if (image == NULL)
				on_destroy(&program);
			program.textures[i++] = image;
			mlx_put_image_to_window(program.mlx, program.window, image, \
			coords.x * TILE_OFFSET, coords.y * TILE_OFFSET);
			if (!image)
				on_destroy(&program);
			put_string(program);
		}
	}
}
