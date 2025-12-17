/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tal-yafi <tal-yafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:35:59 by tal-yafi          #+#    #+#             */
/*   Updated: 2024/05/02 16:57:28 by tal-yafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	ft_array_len(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

void	ft_array_cleaner(void **array, int position)
{
	while (position != 0)
	{
		free(array[position]);
		position--;
	}
	free(array[position]);
	free (array);
}

static void	ft_iter_print(char *env)
{
	int	i;

	i = 0;
	if (!env[i] || env[0] == '|')
		return ;
	printf("declare -x ");
	while (env[i] != '=')
	{
		printf("%c", env[i]);
		i++;
	}
	printf("=\"");
	i++;
	while (env[i])
	{
		printf("%c", env[i]);
		i++;
	}
	printf("\"\n");
}

int	ft_print_env(char **envp)
{
	char	**n_e;
	int		i;
	int		j;
	int		k;

	n_e = ft_dup_envp(envp);
	if (!n_e)
		return (1);
	k = -1;
	while (n_e[++k])
	{
		j = 0;
		i = k;
		while (i < ft_array_len(n_e) && j < ft_array_len(n_e))
		{
			j = 0;
			while (j <= ft_array_len(n_e) && ft_strcmp(n_e[i], n_e[j]) <= 0)
				j++;
			if (j <= ft_array_len(n_e) && ft_strcmp(n_e[i], n_e[j]) > 0)
				i = j;
		}
		ft_iter_print(n_e[i]);
		ft_been_printed(n_e[i]);
	}
	return (ft_array_cleaner((void **)n_e, ft_array_len(n_e)), 0);
}

char	**ft_dup_envp(char **envp)
{
	char	**dup_env;
	int		env_size;
	int		j;

	if (!envp)
		return (NULL);
	env_size = ft_array_len(envp);
	dup_env = ft_calloc(env_size + 1, sizeof(char *));
	if (!dup_env)
		return (NULL);
	j = 0;
	while (j < env_size)
	{
		dup_env[j] = ft_strdup(envp[j]);
		if (!dup_env[j])
		{
			ft_array_cleaner((void **)dup_env, j);
			return (ft_putendl_fd(ER_MALLOC_FUNC, 2), NULL);
		}
		j++;
	}
	dup_env[j] = NULL;
	return (dup_env);
}
