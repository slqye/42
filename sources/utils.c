/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:22 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/05 15:41:11 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

int	split_counter(char **value)
{
	int	i;

	i = -1;
	while (value[i] != NULL)
		i++;
	return (i);
}

void	s_free(char **value)
{
	int	i;

	i = -1;
	while (value[++i] != NULL)
		free(value[i]);
	free(value);
}

void	exec_paths(char ***stock, char **split, int i)
{
	char	**holder;
	char	*path;
	char	*cmd;

	holder = ft_split(&(stock[1][i][5]), ':');
	if (holder == NULL)
		return (perror("split"), exit(EXIT_FAILURE));
	i = -1;
	while (holder[++i] != 0)
	{
		path = ft_strjoin(holder[i], "/");
		cmd = ft_strjoin(path, split[0]);
		execve(cmd, split, NULL);
		free(cmd);
		free(path);
	}
	ft_putstr_fd(split[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (s_free(split), s_free(holder), exit(EXIT_FAILURE));
}
