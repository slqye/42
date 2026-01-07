/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 17:18:42 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

sig_atomic_t	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_program	*program;

	program = ft_calloc(1, sizeof(t_program));
	if (!program)
		return (1);
	program->argc = argc;
	program->argv = argv;
	program->envp = ft_dup_envp(envp);
	program->lexer = NULL;
	program->ast = NULL;
	program->exit = 0;
	prompt("minishell$ ", program);
	return (free(program), 0);
}
