/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:14:38 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/23 18:28:15 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"
#include "get_next_line.h"

char	*norminetted_heredoc(void)
{
	ft_putstr_fd("> ", 1);
	return (get_next_line(0));
}

int	run_heredoc(t_tree *node)
{
	char	*value;
	int		*fds;

	fds = ft_calloc(2, sizeof(int));
	if (!fds)
		return (1);
	if (pipe(fds) == -1)
		return (ft_putendl_fd(ER_PIPE_FUNC, 2), 1);
	node->heredoc = fds;
	while (TRUE)
	{
		value = norminetted_heredoc();
		if (!value && g_sig == SIGINT)
			return (sclose(fds[1]), 1);
		if (!value)
			return (sclose(fds[1]), ft_putendl_fd(HEREDOC_STOP, 2), 0);
		if (ft_strlen(node->value) == ft_strlen(value) - 1)
		{
			if (ft_strncmp(node->value, value, ft_strlen(value) - 1) == 0)
				return (sclose(fds[1]), free(value), 0);
		}
		write(fds[1], value, ft_strlen(value));
		free(value);
	}
	return (0);
}

int	search_heredoc(t_tree *node)
{
	t_tree	*holder;

	holder = node;
	if (node->type == T_WORD)
		node = node->left;
	while (node)
	{
		if (node->type == T_DL_REDIRECTION)
		{
			if (run_heredoc(node) != 0)
				return (1);
		}
		node = node->left;
	}
	node = holder;
	return (0);
}

int	setup_heredocs(t_tree *tree)
{
	int	res;

	res = 0;
	if (tree->right)
		res = setup_heredocs(tree->right);
	if (res == 0 && search_heredoc(tree->left) != 0)
		return (1);
	return (res);
}
