/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:13:37 by uwywijas          #+#    #+#             */
/*   Updated: 2023/11/28 20:34:26 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_convert_c(int value);
int		ft_convert_d(int value);
int		ft_convert_i(int value);
int		ft_convert_p(void *value);
int		ft_convert_s(char *value);
int		ft_convert_u(unsigned int value);
int		ft_convert_x(unsigned int value);
int		ft_convert_xx(unsigned int value);
char	*ft_strchr(const char *s, int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(long n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

#endif