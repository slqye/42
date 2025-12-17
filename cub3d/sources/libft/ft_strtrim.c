/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:46:30 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:09:16 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_passf(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_isinset(s1[i], set))
		i++;
	return (i);
}

static int	ft_passl(char const *s1, char const *set, int cursor)
{
	int	i;
	int	j;

	i = cursor;
	while (s1[i] != '\0')
	{
		j = i;
		while (ft_isinset(s1[j], set))
		{
			if (s1[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*result;

	if (s1 == NULL)
		return (NULL);
	i = ft_passf(s1, set);
	result = malloc(sizeof(char) * (ft_passl(s1, set, i) - i + 1));
	if (result == NULL)
		return (NULL);
	j = 0;
	while (i < ft_passl(s1, set, ft_passf(s1, set)))
	{
		result[j] = s1[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}
