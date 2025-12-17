/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:56:10 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:09:13 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	convert;

	i = 0;
	convert = c;
	if (convert == 0)
		return ((char *) &s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == convert && ft_strchr((char *) &s[i + 1], convert) == 0)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}
