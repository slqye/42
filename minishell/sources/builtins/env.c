/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:14:21 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 15:00:42 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	is_env_containing(t_program *program, char *key)
{
	int	len_s1;
	int	len_s2;
	int	i;

	i = -1;
	while (program->envp[++i])
	{
		len_s1 = ft_strlen(program->envp[i]) - \
		ft_strlen(ft_strchr(program->envp[i], '='));
		len_s2 = ft_strlen(key) - ft_strlen(ft_strchr(key, '='));
		if (len_s1 == len_s2)
		{
			if (ft_strncmp(program->envp[i], key, len_s1) == 0)
				return (1);
		}
	}
	return (0);
}

void	ft_env(t_program *program)
{
	int	i;

	i = 0;
	while (program->envp && program->envp[i])
	{
		printf("%s\n", program->envp[i]);
		i++;
	}
}
