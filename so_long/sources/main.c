/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:47:33 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/13 17:36:51 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include "../includes/player.h"
#include "../includes/rw_mlx.h"

void	init_textures(void **textures, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		textures[i] = NULL;
		i++;
	}
}

int	check_map_file(char *filename)
{
	char	*checker;

	checker = ft_strrchr(&filename[1], '.');
	if (checker == NULL)
		return (0);
	if (ft_strlen(checker) == 4)
	{
		if (ft_strncmp(checker, ".ber", 4) == 0)
			return (1);
	}
	return (0);
}

void	game_loop(t_program program)
{
	if (!program.window)
	{
		mlx_destroy_display(program.mlx);
		free(program.mlx);
		freetab(program.map->data, program.map->size.y);
		free(program.map);
		free(program.textures);
		exit(0);
	}
	program.current_psprite = TEXTR_PLAYER_3;
	show_map(program);
	mlx_hook(program.window, KEYCODE_CLOSED, 0, &on_destroy, &program);
	mlx_key_hook(program.window, &on_keyinput, &program);
	mlx_loop(program.mlx);
}

void	arg_checks(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments.\n", 1), \
	exit(EXIT_FAILURE));
	if (!check_map_file(argv[1]))
		return (ft_putstr_fd("Error\nProbleme with filename.\n", 1), \
	exit(EXIT_FAILURE));
}

int	main(int argc, char **argv)
{
	t_vector2	window_size;
	t_program	program;
	t_map		*map;

	arg_checks(argc, argv);
	map = get_map(argv[1]);
	if (map == NULL)
		return (ft_putstr_fd("Error\nWrong map format.\n", 1), 0);
	window_size.x = map->size.x * TILE_OFFSET;
	window_size.y = (map->size.y + 1) * TILE_OFFSET;
	program.textures = malloc(sizeof(void *) * (map->size.x * \
	(map->size.y + 1)));
	if (program.textures == NULL)
		return (freetab(map->data, map->size.y), free(map), 0);
	init_textures(program.textures, map->size.x * (map->size.y + 1));
	program.map = map;
	program.mlx = mlx_init();
	if (!program.mlx)
		return (freetab(program.map->data, program.map->size.y), \
	free(program.map), free(program.textures), 0);
	program.movements = 0;
	program.window = mlx_new_window(program.mlx, window_size.x, window_size.y, \
	"so_long");
	game_loop(program);
	return (0);
}
