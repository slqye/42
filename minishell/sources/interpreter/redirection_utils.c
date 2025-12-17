/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:14:39 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/15 17:44:02 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

void	*redirect_setup(t_tree *node, t_tree **holder, int *fds)
{
	*holder = node;
	fds[0] = -1;
	fds[1] = -1;
	if (node == T_WORD)
		node = node->left;
	return (NULL);
}

void	setup_io_fds(int *rifd, int *rofd, int *ifd, int *ofd)
{
	if (*rifd != -1)
	{
		sclose(*ifd);
		*ifd = *rifd;
	}
	if (*rofd != -1)
	{
		sclose(*ofd);
		*ofd = *rofd;
	}
}
