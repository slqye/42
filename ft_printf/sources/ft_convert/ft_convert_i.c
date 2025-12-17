/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:17:32 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:37:43 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_getlength(long n)
{
	if (n < 10)
		return (1);
	return (1 + ft_getlength(n / 10));
}

int	ft_convert_i(int value)
{
	ft_putnbr_fd(value, 1);
	if (value < 0)
	{
		if (value == -2147483648)
			value += 1;
		value *= -1;
		return (ft_getlength((int) value) + 1);
	}
	return (ft_getlength((int) value));
}
