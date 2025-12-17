/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:02:46 by slaye             #+#    #+#             */
/*   Updated: 2024/05/02 17:25:54 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	get_envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	is_same_key(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1) - ft_strlen(ft_strchr(s1, '='));
	len_s2 = ft_strlen(s2) - ft_strlen(ft_strchr(s2, '='));
	if (len_s1 == len_s2)
	{
		if (ft_strncmp(s1, s2, len_s1) == 0)
			return (1);
	}
	return (0);
}

int	add_to_envp(t_program *program, char *value)
{
	char	**result;
	int		length;
	int		i;

	length = get_envp_size(program->envp) + 2;
	result = ft_calloc(length, sizeof(char *));
	if (!result)
		return (1);
	i = -1;
	while (++i < length - 2)
	{
		result[i] = ft_strdup(program->envp[i]);
		if (!result[i])
			return (perror("malloc"), 1);
	}
	result[i] = ft_strdup(value);
	if (!result[i])
		return (perror("malloc"), 1);
	result[i + 1] = NULL;
	free_envp(program->envp);
	program->envp = result;
	return (0);
}

int	remove_to_envp(t_program *program, char *value)
{
	char	**result;
	int		length;
	int		i;
	int		j;

	length = get_envp_size(program->envp) + 1;
	result = ft_calloc(length, sizeof(char *));
	if (!result)
		return (1);
	i = -1;
	j = 0;
	while (++i < length - 1)
	{
		if (is_same_key(program->envp[i], value))
			j--;
		else
		{
			result[j] = ft_strdup(program->envp[i]);
			if (!result[j])
				return (perror("malloc"), 1);
		}
		j++;
	}
	free_envp(program->envp);
	return (result[j] = NULL, program->envp = result, 0);
}
