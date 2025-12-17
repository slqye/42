/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:17:37 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:37:47 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_convert_s(char *value)
{
	if (!value)
		return (ft_putstr_fd("(null)", 1), 6);
	ft_putstr_fd(value, 1);
	return (ft_strlen(value));
}
