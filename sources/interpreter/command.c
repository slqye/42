/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:02:21 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/01 14:40:21 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	get_node_size(t_tree *node, int select)
{
	t_tree	*holder;
	int		result;

	holder = node;
	result = 0;
	if (!node || (select != 0 && select != 1))
		return (0);
	while (node)
	{
		if (select == 0)
			node = node->left;
		else
			node = node->right;
		result++;
	}
	node = holder;
	return (result);
}

char	**get_cmd_option(t_tree *node)
{
	t_tree	*holder;
	char	**result;
	int		size;
	int		i;

	i = -1;
	holder = node;
	size = get_node_size(node, 1);
	result = ft_calloc(size + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (++i < size)
	{
		result[i] = node->value;
		node = node->right;
	}
	result[i] = NULL;
	node = holder;
	return (result);
}

char	*get_envp_path(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
	}
	return (NULL);
}

void	try_paths(char *cmd, char **argv, char **paths, t_program *program)
{
	char	*holder;
	char	*builded_cmd;
	int		i;

	i = -1;
	while (paths[++i])
	{
		holder = ft_strjoin("/", cmd);
		builded_cmd = ft_strjoin(paths[i], holder);
		check_perms(program, builded_cmd);
		execve(builded_cmd, argv, program->envp);
		free(holder);
		free(builded_cmd);
	}
}

void	path_execve(char *cmd, char **argv, t_program *program)
{
	char	*path;
	char	**paths;

	paths = NULL;
	if (ft_strchr(cmd, '/') != NULL)
		execve(cmd, argv, program->envp);
	else
	{
		path = get_envp_path(program->envp);
		if (!path)
			return (safe_print(argv[0], ER_CMD_NFOUND, NULL, 2), \
			free_exit(program, 127));
		paths = ft_split(path, ':');
		if (!paths)
			return (ft_putendl_fd(ER_MALLOC_FUNC, 2), free_exit(program, 1));
		try_paths(cmd, argv, paths, program);
	}
	return (free(argv), free_path_split(paths), per_cmd_nfound(program, cmd));
}
