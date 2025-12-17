/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:49:49 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/30 15:11:45 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	f_pipe_left(t_program *program, t_tree *node, t_fds *fds)
{
	int	id;

	id = fork();
	if (id == -1)
		return (ft_putendl_fd(ER_FORK_FUNC, 2), -1);
	if (id == 0)
	{
		sclose(fds->pofd);
		sclose(fds->ifd);
		if (program->pipelvl == 0 && !node->right)
		{
			close(fds->pifd);
			return (execute_ast(program, node->left, fds->ifd, fds->ofd), 0);
		}
		else
			return (execute_ast(program, node->left, fds->pifd, fds->ofd), 0);
	}
	else
		return (id);
}

void	f_pipe_right(t_program *program, t_tree *node, t_fds *fds)
{
	int	id;

	id = fork();
	if (id == -1)
		return (ft_putendl_fd(ER_FORK_FUNC, 2));
	if (id == 0)
	{
		program->pipelvl++;
		sclose(fds->pifd);
		sclose(fds->ofd);
		if (node->right && !node->right->right)
			execute_ast(program, node->right->left, fds->ifd, fds->pofd);
		else
			execute_ast(program, node->right, fds->ifd, fds->pofd);
	}
}

void	f_pipe(t_program *program, t_tree *node, int ifd, int ofd)
{
	t_fds	fds;
	int		hfds[2];
	int		left_id;
	int		status;

	if (pipe(hfds) == -1)
		return (ft_putendl_fd(ER_PIPE_FUNC, 2));
	fds.ifd = ifd;
	fds.ofd = ofd;
	fds.pifd = hfds[0];
	fds.pofd = hfds[1];
	f_pipe_right(program, node, &fds);
	left_id = f_pipe_left(program, node, &fds);
	sclose(ifd);
	sclose(ofd);
	sclose(fds.pifd);
	sclose(fds.pofd);
	if (left_id != -1 && left_id != 0)
	{
		waitpid(left_id, &status, 0);
		update_exit_status(program, status);
	}
	if (program->pipelvl != 0)
		free_exit(program, EXIT_SUCCESS);
}

void	execute_cmd(t_program *p, t_tree *node, int ifd, int ofd)
{
	int	rifd;
	int	rofd;

	sig_default();
	p->hofd = ofd;
	p->pipelvl = -1;
	if (!node && p->pipelvl != 0)
		return (sclose(ifd), sclose(ofd), free_exit(p, EXIT_SUCCESS));
	else if (node->type != T_WORD)
		return (sclose(ifd), sclose(ofd), get_cmd_fds(p, node, &rifd, &rofd), \
	sclose(rifd), sclose(rofd), free_exit(p, EXIT_SUCCESS));
	get_cmd_fds(p, node, &rifd, &rofd);
	setup_io_fds(&rifd, &rofd, &ifd, &ofd);
	cmd_duping(p, ifd, ofd);
	check_and_exec_builtin(p, node);
	path_execve(node->value, get_cmd_option(node), p);
	free_exit(p, EXIT_FAILURE);
}

void	execute_ast(t_program *program, t_tree *node, int ifd, int ofd)
{
	if (!node)
		return (sclose(ifd), sclose(ofd), free_exit(program, EXIT_SUCCESS));
	if (node->type == T_PIPE)
		f_pipe(program, node, ifd, ofd);
	else
		execute_cmd(program, node, ifd, ofd);
}
