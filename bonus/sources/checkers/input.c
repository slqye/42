/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:46:14 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/15 17:42:03 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/imports.h"
#include "../../includes/commons.h"

int	get_tab_length(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int	is_tab_int(char **tab, int length)
{
	int	i;

	i = -1;
	while (++i < length)
	{
		if (ft_atol(tab[i]) > INT_MAX || ft_atol(tab[i]) < INT_MIN \
		|| ft_strlen(tab[i]) >= 12)
			return (0);
	}
	return (1);
}

int	is_tab_unique(char **tab, int length)
{
	int	i;
	int	j;
	int	holder;

	i = -1;
	while (++i < length)
	{
		j = -1;
		while (++j < length)
		{
			if (ft_strlen(tab[i]) >= ft_strlen(tab[j]))
				holder = ft_strlen(tab[i]);
			else
				holder = ft_strlen(tab[j]);
			if (j != i && ft_strncmp(tab[i], tab[j], holder) == 0)
				return (0);
		}
	}
	return (1);
}

int	is_tab_valid(char **tab, int length)
{
	int		i;
	int		j;

	i = -1;
	while (++i < length)
	{
		j = -1;
		if (ft_strlen(tab[i]) == 0)
			return (0);
		if (ft_strlen(tab[i]) == 2 \
		&& tab[i][0] == '-' && tab[i][1] == '0')
			return (0);
		while (++j < (int) ft_strlen(tab[i]))
		{
			if (j == 0 && tab[i][j] == '-')
				continue ;
			else if (!ft_isdigit(tab[i][j]))
				return (0);
		}
	}
	if (!is_tab_unique(tab, length))
		return (0);
	if (!is_tab_int(tab, length))
		return (0);
	return (1);
}
