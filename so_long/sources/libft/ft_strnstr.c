/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:16:37 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:09:11 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (s2[0] == '\0')
		return ((char *) s1);
	if (len <= 0)
		return (0);
	while (i < len && s1[i] != '\0')
	{
		if (ft_strncmp(&((char *) s1)[i], s2, ft_strlen(s2)) == 0 &&
		i + ft_strlen(s2) <= len)
			return (&((char *) s1)[i]);
		i++;
	}
	return (0);
}
