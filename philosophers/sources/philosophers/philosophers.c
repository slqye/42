/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:30:16 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 12:28:38 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	philosophers(int argc, char **argv)
{
	t_philosopher	**philosophers;
	int				i;
	int				total_eat;

	i = -1;
	total_eat = -1;
	philosophers = malloc(sizeof(t_philosopher **) * (ft_atol(argv[1]) + 1));
	if (philosophers == NULL)
		return ((void) NULL);
	while (++i < ft_atol(argv[1]))
	{
		philosophers[i] = create_philosopher(i + 1, argc, argv);
		if (philosophers[i] == NULL)
			return (free_philosophers(philosophers, i), ft_error("error\n"));
	}
	philosophers[ft_atol(argv[1])] = NULL;
	if (f_add_forks(philosophers) != 0)
		return (free_philosophers(philosophers, i), ft_error("fork: error\n"));
	if (argc == 6)
		total_eat = ft_atol(argv[5]);
	start_threads(philosophers, total_eat);
	free_philosophers(philosophers, i);
}
