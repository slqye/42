/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:23:53 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/01 14:42:21 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	is_next_fd(t_tree *node, int type)
{
	t_tree	*holder;

	if (!node)
		return (0);
	holder = node;
	while (node)
	{
		if (type == 0)
		{
			if (node->type == T_SL_REDIRECTION \
			|| node->type == T_DL_REDIRECTION)
				return (node = holder, 1);
		}
		else
		{
			if (node->type == T_SR_REDIRECTION \
			|| node->type == T_DR_REDIRECTION)
				return (node = holder, 1);
		}
		node = node->left;
	}
	node = holder;
	return (0);
}

void	ifd_handler(t_program *program, t_tree *node, int *fds)
{
	fds[0] = open(node->value, O_RDONLY);
	if (fds[0] == -1)
	{
		sclose(fds[0]);
		sclose(fds[1]);
		sclose(program->hofd);
		return (safe_print("minishell: ", node->value, ER_FILE_NFOUND, 2), \
		free_exit(program, EXIT_FAILURE));
	}
	else if (is_next_fd(node->left, 0) == 1)
		sclose(fds[0]);
}

void	ofd_handler(t_program *program, t_tree *node, int *fds)
{
	if (node->type == T_SR_REDIRECTION)
		fds[1] = open(node->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fds[1] = open(node->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fds[1] == -1)
	{
		sclose(fds[0]);
		sclose(fds[1]);
		return (ft_putendl_fd(ER_OPEN_FAILED, 2), \
		free_exit(program, EXIT_FAILURE));
	}
	else if (is_next_fd(node->left, 1) == 1)
		sclose(fds[1]);
}

void	get_cmd_fds(t_program *program, t_tree *node, int *ifd, int *ofd)
{
	t_tree	*holder;
	t_tree	*last;
	int		fds[2];

	last = redirect_setup(node, &holder, fds);
	while (node)
	{
		if (node->type == T_SL_REDIRECTION)
		{
			ifd_handler(program, node, fds);
			last = node;
		}
		else if (node->type == T_DL_REDIRECTION)
		{
			sclose(fds[0]);
			last = node;
		}
		else if (node->type == T_SR_REDIRECTION || node->type == TDR_R)
			ofd_handler(program, node, fds);
		node = node->left;
	}
	node = holder;
	if (last && last->type == T_DL_REDIRECTION)
		fds[0] = last->heredoc[0];
	return (*ifd = fds[0], *ofd = fds[1], (void) NULL);
}
