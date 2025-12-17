/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:24:32 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:08:37 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == 0 && src == 0)
		return (dest);
	if (src < dest)
	{
		i = -1;
		while (++i < n)
			((char *) dest)[n - i - 1] = ((char *) src)[n - i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			((char *) dest)[i] = ((char *) src)[i];
	}
	return (dest);
}
