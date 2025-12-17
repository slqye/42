/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:04:58 by slaye             #+#    #+#             */
/*   Updated: 2024/06/20 13:45:06 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	check_color(t_program *program, char *color)
{
	char	**split;
	int		i;
	int		counter;

	split = ft_split(color, ',');
	if (!split)
		fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
	counter = -1;
	while (split[++counter])
	{
		i = -1;
		while (split[counter][++i])
		{
			if (!ft_isdigit(split[counter][i]) || ft_strlen(split[counter]) > 3)
			{
				free_split(split);
				fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
			}
		}
	}
	free_split(split);
	if (counter != 3)
		fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
}

void	check_lst_grid_chars(t_program *program, t_list *lst_grid)
{
	t_list	*holder;
	char	c;
	int		i;
	int		spawn;

	spawn = 0;
	holder = lst_grid;
	while (holder)
	{
		i = -1;
		while (((char *) holder->content)[++i] != '\0')
		{
			c = ((char *) holder->content)[i];
			if (c != EMPTY && c != WALL && c != NORTH && c != SOUTH \
			&& c != EST && c != WEST && c != ' ')
				fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
			else if (c == NORTH || c == SOUTH || c == EST || c == WEST)
				spawn++;
		}
		holder = holder->next;
	}
	if (spawn != 1)
		fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
}

void	set_grid_array(t_program *program)
{
	t_list	*holder;
	int		size;
	int		i;

	size = ft_lstsize(program->map->lst_grid);
	program->map->grid = ft_calloc(size + 1, sizeof(char *));
	if (!program->map->grid)
		fexit(program, EXIT_FAILURE, ER_MALLOC, STDERR_FILENO);
	holder = program->map->lst_grid;
	i = 0;
	while (holder)
	{
		program->map->grid[i] = holder->content;
		holder = holder->next;
		i++;
	}
	program->map->grid[i] = NULL;
}

void	check_grid_norm(t_program *program, char **grid)
{
	int	y;
	int	x;

	(void) program;
	y = -1;
	while (grid[++y] != NULL)
	{
		x = -1;
		while (grid[y][++x] != '\0')
			check_cell_border(program, grid, y, x);
	}
}

void	map_checker(t_program *program)
{
	check_color(program, program->map->f);
	check_color(program, program->map->c);
	check_lst_grid_chars(program, program->map->lst_grid);
	set_grid_array(program);
	check_grid_norm(program, program->map->grid);
}
