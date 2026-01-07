/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:45:37 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 17:20:04 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

static int	ft_skip_target(char **envp, char **new_e, int j)
{
	while (j < ft_array_len(envp) && envp[j + 1])
	{
		new_e[j] = ft_strdup(envp[j + 1]);
		if (!new_e[j])
		{
			ft_array_cleaner((void **)new_e, j);
			return (1);
		}
		j++;
	}
	return (0);
}

static void	ft_smaller_env(t_program *program, int pos)
{
	char	**new_e;
	int		j;

	new_e = ft_calloc(ft_array_len(program->envp) + 1, sizeof(char *));
	if (!new_e)
		return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
	j = 0;
	while (j < ft_array_len(program->envp) - 1 && j != pos)
	{
		new_e[j] = ft_strdup(program->envp[j]);
		if (!new_e[j])
		{
			ft_array_cleaner((void **)new_e, j);
			return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
		}
		j++;
	}
	if (j == pos)
	{
		if (ft_skip_target(program->envp, new_e, j) > 0)
			return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
	}
	ft_array_cleaner((void **)program->envp, ft_array_len(program->envp));
	program->envp = new_e;
}

void	ft_unset(t_program *program, t_tree *node)
{
	char	**argv;
	int		i;
	int		j;
	int		pos;
	int		size;

	argv = get_cmd_option(node);
	if (!argv)
		return ;
	i = 1;
	while (argv[i])
	{
		size = ft_strlen(argv[i]);
		pos = -1;
		while (program->envp && program->envp[++pos])
		{
			j = 0;
			while (program->envp[pos][j] && program->envp[pos][j] != '=')
				j++;
			if (size == j && ft_strncmp(argv[i], program->envp[pos], size) == 0)
				ft_smaller_env(program, pos);
		}
		i++;
	}
	return (free(argv));
}
