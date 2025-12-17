/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:44 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 15:39:16 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	checker(char *value)
{
	if (ft_atol(value) <= 0)
		return (1);
	else if (ft_atol(value) > MINT_MAX)
		return (1);
	else if (ft_strlen(value) > 10)
		return (1);
	return (0);
}

int	check_arg(int argc, char **argv)
{
	if (checker(argv[1]))
		return (0);
	else if (checker(argv[2]))
		return (0);
	else if (checker(argv[3]))
		return (0);
	else if (checker(argv[4]))
		return (0);
	if (argc == 6)
	{
		if (checker(argv[5]))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error("error: args\n"), 0);
	if (!check_arg(argc, argv))
		return (ft_error("error: args\n"), 0);
	philosophers(argc, argv);
	return (0);
}
