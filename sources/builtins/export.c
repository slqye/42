/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tal-yafi <tal-yafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:45:37 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 17:34:39 by tal-yafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

static int	ft_update_env(t_program *program, char *argv)
{
	int	pos;

	pos = ft_to_update(program, argv);
	if (pos >= 0)
	{
		free (program->envp[pos]);
		program->envp[pos] = ft_strdup(argv);
		if (!program->envp[pos])
			return (1);
		return (-1);
	}
	return (0);
}

static void	ft_add_to_env(char *argv, char **new_env, int j)
{
	if (argv && ft_strchr(argv, '='))
	{
		new_env[j] = ft_strdup(argv);
		if (!new_env[j])
		{
			ft_array_cleaner((void **)new_env, j);
			return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
		}
	}
	new_env[j + 1] = NULL;
}

static void	ft_bigger_env(t_program *program, char *argv)
{
	char	**new_e;
	int		j;

	new_e = ft_calloc(ft_array_len(program->envp) + 2, sizeof(char *));
	if (!new_e)
		return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
	j = 0;
	while (j < ft_array_len(program->envp))
	{
		new_e[j] = ft_strdup(program->envp[j]);
		if (!new_e[j])
		{
			ft_array_cleaner((void **)new_e, j);
			return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
		}
		j++;
	}
	new_e[j] = NULL;
	ft_array_cleaner((void **)program->envp, j);
	ft_add_to_env(argv, new_e, j);
	program->envp = new_e;
}

static void	ft_new_env(t_program *program, char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (ft_update_env(program, argv[i]) > 0)
			return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
		if (ft_update_env(program, argv[i]) == 0)
		{
			ft_bigger_env(program, argv[i]);
		}
		i++;
	}
}

void	ft_export(t_program *program, t_tree *node)
{
	char	**argv;
	int		i;

	argv = get_cmd_option(node);
	if (!argv)
		return ;
	i = 0;
	while (argv[++i])
	{
		if (ft_valid_arg(argv[i]) > 0)
			return (safe_print("minishell: export: `", argv[i],
					ER_EXPORT_ID, 2), free(argv));
	}
	if (i == 1)
	{
		if (ft_print_env(program->envp) > 0)
			return ((void)ft_putendl_fd(ER_MALLOC_FUNC, 2));
	}
	else if (i > 1)
	{
		i = ft_env_args(argv);
		if (i != 0)
			ft_new_env(program, argv);
	}
	return (free(argv));
}
