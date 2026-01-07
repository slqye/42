/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:33:18 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 14:05:02 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

char	*readline_handler(t_program *program, char *value)
{
	char	*line_read;

	line_read = readline(value);
	if (line_read && line_read[0] != ""[0])
		add_history(line_read);
	if (g_sig == SIGINT)
		program->exit = 130;
	return (line_read);
}

void	free_to_null(t_program *program, int select)
{
	if (select == 0)
		return (free_lexer(program->lexer), (void)(program->lexer = NULL));
	else
		return (free_tree(program->ast), (void)(program->ast = NULL));
}

void	prompt(char *value, t_program *program)
{
	char	*line_read;

	while (TRUE)
	{
		setup_signals();
		line_read = readline_handler(program, value);
		if (!line_read)
			return (ft_putendl_fd("exit", 2), free_exit(program, EXIT_SUCCESS));
		if (line_read)
		{
			program->lexer = lexer(line_read, program);
			free(line_read);
			if (program->lexer)
				program->ast = ast(program->lexer);
			if (program->ast && program->lexer)
				interpreter(program->ast, program);
			if (program->lexer)
				free_to_null(program, 0);
			if (program->ast)
				free_to_null(program, 1);
		}
		else if (line_read != NULL)
			free(line_read);
		g_sig = 0;
	}
}
