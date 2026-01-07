/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:08:01 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/09 18:00:59 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rw_mlx.h"

t_image	get_image(void *mlx, char *path)
{
	t_image	img;

	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	if (!img.pointer)
		return (img);
	img.pixels = mlx_get_data_addr(img.pointer, &img.bits_per_pixel, \
	&img.line_size, &img.endian);
	return (img);
}
