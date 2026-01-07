/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:17:39 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:37:49 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_getlength(unsigned int n)
{
	if (n < 10)
		return (1);
	return (1 + ft_getlength(n / 10));
}

int	ft_convert_u(unsigned int value)
{
	ft_putnbr_fd(value, 1);
	return (ft_getlength(value));
}
