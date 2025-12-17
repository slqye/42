/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pipe_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:22:00 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 18:05:24 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

void	update_exit_status(t_program *program, int status)
{
	if (WIFEXITED(status))
		program->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit\n", 5);
		program->exit = WTERMSIG(status) + 128;
	}
}

void	cmd_duping(t_program *program, int ifd, int ofd)
{
	if (dup2(ifd, STDIN_FILENO) == -1)
		return (sclose(ifd), sclose(ofd), free_exit(program, EXIT_FAILURE));
	sclose(ifd);
	if (dup2(ofd, STDOUT_FILENO) == -1)
		return (sclose(ofd), free_exit(program, EXIT_FAILURE));
	sclose(ofd);
}
