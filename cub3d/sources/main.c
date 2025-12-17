/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:09:52 by slaye             #+#    #+#             */
/*   Updated: 2024/06/28 11:47:01 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	p_verify(t_program *program)
{
	if (program->argc != 2)
		fexit(program, EXIT_FAILURE, ER_ARGS, STDERR_FILENO);
	if (ft_strrchr(program->argv[1], '.') == NULL)
		fexit(program, EXIT_FAILURE, ER_ARGS, STDERR_FILENO);
	if (ft_strlen(ft_strrchr(program->argv[1], '.')) != 4)
		fexit(program, EXIT_FAILURE, ER_ARGS, STDERR_FILENO);
	if (ft_strncmp(ft_strrchr(program->argv[1], '.'), ".cub", 4) != 0)
		fexit(program, EXIT_FAILURE, ER_ARGS, STDERR_FILENO);
}

t_program	*p_setup(int argc, char **argv)
{
	t_program	*program;

	program = ft_calloc(1, sizeof(t_program));
	if (!program)
		fexit(program, EXIT_FAILURE, ER_MALLOC, STDERR_FILENO);
	program->argc = argc;
	program->argv = argv;
	program->map = NULL;
	program->fd = -1;
	program->player = NULL;
	program->mlx = NULL;
	program->screen = NULL;
	program->minimap = NULL;
	program->player_img = NULL;
	program->is_terminated = 0;
	return (program);
}

t_map	*m_setup(t_program *program)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		fexit(program, EXIT_FAILURE, ER_MALLOC, STDERR_FILENO);
	map->file = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
	map->lst_grid = NULL;
	map->grid = NULL;
	map->ratio_x = 1.0;
	map->ratio_y = 1.0;
	return (map);
}

void	setup_textures(t_program *program, t_map *map)
{
	program->t_no = mlx_load_png(map->no);
	if (!program->t_no)
		fexit(program, EXIT_FAILURE, ER_OPEN, STDERR_FILENO);
	program->t_so = mlx_load_png(map->so);
	if (!program->t_so)
		fexit(program, EXIT_FAILURE, ER_OPEN, STDERR_FILENO);
	program->t_we = mlx_load_png(map->we);
	if (!program->t_we)
		fexit(program, EXIT_FAILURE, ER_OPEN, STDERR_FILENO);
	program->t_ea = mlx_load_png(map->ea);
	if (!program->t_ea)
		fexit(program, EXIT_FAILURE, ER_OPEN, STDERR_FILENO);
}

int	main(int argc, char **argv)
{
	t_program	*program;

	program = p_setup(argc, argv);
	program->map = m_setup(program);
	p_verify(program);
	parser(program);
	program->player = s_player(program);
	setup_textures(program, program->map);
	s_window(program);
	fexit(program, EXIT_SUCCESS, DB_END, STDIN_FILENO);
}
