/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:18:18 by uwywijas          #+#    #+#             */
/*   Updated: 2023/12/08 17:08:46 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
