/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:02:02 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:34:51 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	convert;

	i = 0;
	convert = c;
	while (s[i] != '\0')
	{
		if (s[i] == convert)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == convert)
		return ((char *) &s[i]);
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long n, int fd)
{
	long	value;
	char	input;

	value = (long) n;
	if (value < 0)
	{
		write(fd, "-", 1);
		value *= -1;
	}
	input = '0' + value % 10;
	if (value < 10)
	{
		write(fd, &input, 1);
		return ;
	}
	ft_putnbr_fd(value / 10, fd);
	write(fd, &input, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ((void) NULL);
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
