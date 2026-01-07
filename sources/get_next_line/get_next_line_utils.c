/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:56:49 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 17:25:51 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_gnlstrlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_gnlstrchr(const char *s, int c)
{
	int		i;
	char	convert;

	i = 0;
	convert = c;
	while (s[i] != '\0')
	{
		if (s[i] == convert)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == convert)
		return ((char *) &s[i]);
	return (0);
}

char	*ft_gnlstrjoin(char *s1, char const *s2)
{
	char		*result;
	size_t		length;
	size_t		i;
	size_t		j;

	if (s1 == NULL || s2 == NULL)
		return (free(s1), NULL);
	result = malloc(sizeof(char) * (ft_gnlstrlen(s1) + ft_gnlstrlen(s2) + 1));
	if (result == NULL)
		return (free(s1), NULL);
	i = -1;
	length = ft_gnlstrlen(s1);
	while (++i < length)
		result[i] = s1[i];
	j = -1;
	length = ft_gnlstrlen(s2);
	while (++j < length)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	free(s1);
	return (result);
}
