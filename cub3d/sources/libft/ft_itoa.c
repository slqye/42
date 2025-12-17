/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:14:35 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:08:12 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlength(long n)
{
	if (n < 10)
		return (1);
	return (1 + ft_getlength(n / 10));
}

static void	ft_swap(char *a, char *b)
{
	char	x;

	x = *a;
	*a = *b;
	*b = x;
}

static void	ft_reverse_str(char *str)
{
	size_t	i;
	int		length;

	i = 0;
	length = ft_strlen(str);
	while (i < ft_strlen(str) / 2)
	{
		ft_swap(&str[i], &str[length - i - 1]);
		i++;
	}
}

static void	ft_check_negative(long *v, int *is_negative)
{
	*is_negative = 0;
	if (*v < 0)
	{
		*v *= -1;
		*is_negative = 1;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		length;
	int		i;
	long	v;
	int		is_negative;

	v = (long) n;
	ft_check_negative(&v, &is_negative);
	length = ft_getlength(v);
	result = malloc(sizeof(char) * (length + is_negative + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i < length)
	{
		result[i] = '0' + v % 10;
		v /= 10;
	}
	if (is_negative)
		result[i] = '-';
	result[length + is_negative] = '\0';
	ft_reverse_str(result);
	return (result);
}
