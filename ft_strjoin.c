/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:40:30 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:08:57 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			length;
	char		*result;
	size_t		i;
	size_t		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	length = ft_strlen(s1);
	while (++i < (size_t) length)
		result[i] = s1[i];
	j = -1;
	length = ft_strlen(s2);
	while (++j < (size_t) length)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}
