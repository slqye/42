/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:14:21 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:34:42 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_convert(char c, va_list args)
{
	if (c == 'c')
		return (ft_convert_c(va_arg (args, int)));
	else if (c == 's')
		return (ft_convert_s(va_arg (args, char *)));
	else if (c == 'p')
		return (ft_convert_p(va_arg (args, void *)));
	else if (c == 'd')
		return (ft_convert_d(va_arg (args, int)));
	else if (c == 'i')
		return (ft_convert_i(va_arg (args, int)));
	else if (c == 'u')
		return (ft_convert_u(va_arg (args, unsigned int)));
	else if (c == 'x')
		return (ft_convert_x(va_arg (args, int)));
	else if (c == 'X')
		return (ft_convert_xx(va_arg (args, int)));
	else
		return (ft_putchar_fd('%', 1), 1);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			length[1];
	int			i;
	char		*holder;

	va_start (args, format);
	i = 0;
	length[0] = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			holder = ft_strchr("cspdiuxX%", format[++i]);
			if (holder)
				length[0] += ft_convert(holder[0], args);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			length[0]++;
		}
		i++;
	}
	return (*length);
}
