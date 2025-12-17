/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:17:41 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:37:50 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_counthexa(unsigned int value)
{
	if (value < 16)
		return (1);
	return (1 + ft_counthexa(value / 16));
}

static void	ft_puthexa_lower(unsigned int value)
{
	if (!value)
		return ;
	if (value >= 16)
		ft_puthexa_lower(value / 16);
	ft_putchar_fd("0123456789abcdef\0"[value % 16], 1);
}

int	ft_convert_x(unsigned int value)
{
	if (value == 0)
		return (ft_putchar_fd('0', 1), 1);
	ft_puthexa_lower(value);
	return (ft_counthexa(value));
}
