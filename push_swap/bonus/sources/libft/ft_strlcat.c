/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:36:59 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:08:59 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (dst == NULL && src != NULL && size == 0)
		return (ft_strlen(src));
	if (size == 0)
		return (ft_strlen(src));
	j = 0;
	i = ft_strlen(dst);
	while ((i + j) < size - 1 && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (i > size)
		return (ft_strlen(src) + size);
	return (i + ft_strlen(src));
}
