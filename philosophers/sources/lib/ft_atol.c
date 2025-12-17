/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:27:52 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 15:34:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

static int	ft_iswhitespace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_isnumber(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_pow(int value, int power)
{
	int	result;

	result = 1;
	while (power > 1)
	{
		result *= value;
		power--;
	}
	return (result);
}

static int	ft_numberlen(const char *str)
{
	int	i;

	i = 0;
	while (ft_isnumber(str[i]))
		i++;
	return (i);
}

long	ft_atol(const char *str)
{
	int		length;
	int		positive;
	long	result;
	int		i;
	int		c;

	positive = 1;
	result = 0;
	i = 0;
	c = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (!ft_isnumber(str[i]) && (str[i] != '+' && str[i] != '-'))
		return (0);
	else if (str[i] == '-')
		positive = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	length = ft_numberlen(&str[i]);
	while (ft_isnumber(str[i]))
		result += (str[i++] - '0') * ft_pow(10, length - c++);
	return (result * positive);
}
