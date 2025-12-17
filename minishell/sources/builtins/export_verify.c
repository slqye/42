/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_verify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tal-yafi <tal-yafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:30:38 by tal-yafi          #+#    #+#             */
/*   Updated: 2024/05/02 16:57:37 by tal-yafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	ft_env_args(char **argv)
{
	int	l;
	int	m;
	int	valids;

	l = 0;
	valids = 0;
	while (argv[l])
	{
		m = 0;
		while (argv[l][m])
		{
			if (argv[l][m] == '=')
			{
				valids++;
				break ;
			}
			m++;
		}
		l++;
	}
	return (valids);
}

int	ft_valid_arg(char *argv)
{
	int	i;

	if (argv[0] != '_' && ft_isalpha(argv[0]) == 0)
		return (1);
	i = 1;
	while (argv[i] && argv[i] != '=')
	{
		if (argv[i] != '_' && ft_isalnum(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_to_update(t_program *program, char *argv)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (argv[i] != '=')
		i++;
	while (program->envp[pos])
	{
		j = 0;
		while (program->envp[pos][j] != '=')
			j++;
		if (i == j && ft_strncmp(argv, program->envp[pos], i) == 0)
			return (pos);
		pos++;
	}
	return (-1);
}

void	ft_been_printed(char *line)
{
	int	q;

	q = 0;
	while (line && line[q])
	{
		line[q] = '|';
		q++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
