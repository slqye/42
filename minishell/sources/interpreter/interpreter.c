/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:02:21 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 17:19:36 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	check_solo_cmds(t_program *program, t_tree *ast)
{
	t_tree	*node;
	int		length;

	if (ast->right)
		return (0);
	node = ast->left;
	length = ft_strlen(node->value);
	if (ft_strncmp(node->value, "cd", 2) == 0 && length == 2)
		return (ft_solo_cd(program, node), 1);
	if (ft_strncmp(node->value, "exit", 4) == 0 && length == 4)
		return (program->pipelvl = -1, ft_exit(program, node), 1);
	if (ft_strncmp(node->value, "export", 6) == 0 && length == 6)
		return (ft_export(program, node), 1);
	if (ft_strncmp(node->value, "unset", 5) == 0)
		return (ft_unset(program, node), 1);
	return (0);
}

int	interpreter(t_tree *ast, t_program *program)
{
	program->pipelvl = 0;
	signals_setup_heredocs();
	if (setup_heredocs(ast) != 0)
		return (1);
	sig_ignore();
	if (check_solo_cmds(program, ast) != 0)
		return (0);
	execute_ast(program, ast, 0, 1);
	wait(NULL);
	wait(NULL);
	program->pipelvl = 0;
	return (0);
}
