/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:41:44 by slaye             #+#    #+#             */
/*   Updated: 2024/06/12 17:12:43 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "get_next_line.h"

void	get_map_file(t_program *program)
{
	t_list	*holder;
	char	*value;

	value = get_next_line(program->fd);
	while (value)
	{
		holder = ft_lstnew(value);
		if (!holder)
		{
			free(value);
			fexit(program, EXIT_FAILURE, ER_OPEN, STDERR_FILENO);
		}
		ft_lstadd_back(&program->map->file, holder);
		value = get_next_line(program->fd);
	}
}

void	set_map_vars(t_program *program)
{
	t_list	*holder;

	holder = program->map->file;
	while (holder)
	{
		set_map_vars_loop(program, holder->content);
		holder = holder->next;
	}
}

void	check_map_vars(t_program *program)
{
	t_map	*map;

	map = program->map;
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
}

void	parser(t_program *program)
{
	program->fd = open(program->argv[1], O_RDONLY);
	if (program->fd == -1)
		fexit(program, EXIT_FAILURE, ER_OPEN, STDERR_FILENO);
	get_map_file(program);
	set_map_vars(program);
	check_map_vars(program);
	set_map_grid(program);
	close(program->fd);
	map_checker(program);
}
