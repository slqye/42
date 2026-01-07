/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:48:34 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/13 18:08:27 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/player.h"
#include "../../includes/rw_mlx.h"

void	handler(t_program *program, int select)
{
	if (select == 0)
	{
		ft_putstr_fd("Game lost !\n", 1);
		on_destroy(program);
	}
	else
	{
		ft_putstr_fd("Game win !\n", 1);
		on_destroy(program);
	}
}

void	move_up(t_program *program, t_vector2 coords)
{
	int	is_exit;

	is_exit = 0;
	if (coords.y == 0)
		return ;
	if (program->map->data[coords.y - 1][coords.x] != WALL)
	{
		if (program->map->data[coords.y - 1][coords.x] == EXIT)
			is_exit = 1;
		else if (program->map->data[coords.y - 1][coords.x] == SKEL)
			handler(program, 0);
		if (!is_exit || (is_exit && get_map_char(program->map, COLLECT) == 0))
		{
			program->map->data[coords.y - 1][coords.x] = PLAYER;
			program->map->data[coords.y][coords.x] = FLOOR;
			program->current_psprite = TEXTR_PLAYER_1;
			program->movements++;
			ft_putstr_fd("Movements : ", 1);
			ft_putnbr_fd(program->movements, 1);
			ft_putstr_fd("\n", 1);
		}
		if (is_exit && get_map_char(program->map, COLLECT) == 0)
			handler(program, 1);
	}
}

void	move_down(t_program *program, t_vector2 coords)
{
	int	is_exit;

	is_exit = 0;
	if (coords.y == program->map->size.y)
		return ;
	if (program->map->data[coords.y + 1][coords.x] != WALL)
	{
		if (program->map->data[coords.y + 1][coords.x] == EXIT)
			is_exit = 1;
		else if (program->map->data[coords.y + 1][coords.x] == SKEL)
			handler(program, 0);
		if (!is_exit || (is_exit && get_map_char(program->map, COLLECT) == 0))
		{
			program->map->data[coords.y + 1][coords.x] = PLAYER;
			program->map->data[coords.y][coords.x] = FLOOR;
			program->current_psprite = TEXTR_PLAYER_3;
			program->movements++;
			ft_putstr_fd("Movements : ", 1);
			ft_putnbr_fd(program->movements, 1);
			ft_putstr_fd("\n", 1);
		}
		if (is_exit && get_map_char(program->map, COLLECT) == 0)
			handler(program, 1);
	}
}

void	move_left(t_program *program, t_vector2 coords)
{
	int	is_exit;

	is_exit = 0;
	if (coords.x == 0)
		return ;
	if (program->map->data[coords.y][coords.x - 1] != WALL)
	{
		if (program->map->data[coords.y][coords.x - 1] == EXIT)
			is_exit = 1;
		else if (program->map->data[coords.y][coords.x - 1] == SKEL)
			handler(program, 0);
		if (!is_exit || (is_exit && get_map_char(program->map, COLLECT) == 0))
		{
			program->map->data[coords.y][coords.x - 1] = PLAYER;
			program->map->data[coords.y][coords.x] = FLOOR;
			program->current_psprite = TEXTR_PLAYER_2;
			program->movements++;
			ft_putstr_fd("Movements : ", 1);
			ft_putnbr_fd(program->movements, 1);
			ft_putstr_fd("\n", 1);
		}
		if (is_exit && get_map_char(program->map, COLLECT) == 0)
			handler(program, 1);
	}
}

void	move_right(t_program *program, t_vector2 coords)
{
	int	is_exit;

	is_exit = 0;
	if (coords.x == program->map->size.x)
		return ;
	if (program->map->data[coords.y][coords.x + 1] != WALL)
	{
		if (program->map->data[coords.y][coords.x + 1] == EXIT)
			is_exit = 1;
		else if (program->map->data[coords.y][coords.x + 1] == SKEL)
			handler(program, 0);
		if (!is_exit || (is_exit && get_map_char(program->map, COLLECT) == 0))
		{
			program->map->data[coords.y][coords.x + 1] = PLAYER;
			program->map->data[coords.y][coords.x] = FLOOR;
			program->current_psprite = TEXTR_PLAYER_4;
			program->movements++;
			ft_putstr_fd("Movements : ", 1);
			ft_putnbr_fd(program->movements, 1);
			ft_putstr_fd("\n", 1);
		}
		if (is_exit && get_map_char(program->map, COLLECT) == 0)
			handler(program, 1);
	}
}
