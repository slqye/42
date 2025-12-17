/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:19:34 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/05 15:25:07 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (c == '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (words);
}

static int	ft_splitlen(char const *s, char c, int index)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[index] != c && s[index] != '\0')
	{
		i++;
		index++;
	}
	return (i);
}

static char	**ft_freetab(char **value, int i)
{
	i++;
	while (--i >= 0)
		free(value[i]);
	free(value);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;
	int		global_index;

	if (s == NULL)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	global_index = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			result[++global_index] = ft_substr(s, i, ft_splitlen(s, c, i));
			if (result[global_index] == NULL)
				return (ft_freetab(result, global_index));
			i += ft_splitlen(s, c, i) - 1;
		}
	}
	result[++global_index] = 0;
	return (result);
}
