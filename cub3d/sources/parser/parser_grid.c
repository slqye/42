/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:43:52 by slaye             #+#    #+#             */
/*   Updated: 2024/06/12 17:12:54 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	set_map_grid_loop(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

void	set_map_grid_lst(t_program *program, t_list *node)
{
	t_list	*holder;

	remove_nl(node->content);
	holder = ft_lstnew(node->content);
	if (!holder)
		fexit(program, EXIT_FAILURE, ER_MALLOC, STDERR_FILENO);
	ft_lstadd_back(&program->map->lst_grid, holder);
}

void	set_map_grid(t_program *program)
{
	t_list	*holder;
	int		i;
	int		step;

	holder = program->map->file;
	i = 0;
	step = 0;
	while (holder)
	{
		if (i < 6)
			i += set_map_grid_loop(holder->content);
		else
		{
			if (is_map_chars(holder->content))
				step = 1;
			if (!is_map_chars(holder->content) && step == 1)
				fexit(program, EXIT_FAILURE, ER_MAP, STDERR_FILENO);
			if (step == 1)
				set_map_grid_lst(program, holder);
		}
		holder = holder->next;
	}
}
