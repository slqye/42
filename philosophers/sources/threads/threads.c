/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:55:13 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 12:25:29 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

pthread_t	*create_threads(t_philosopher **philosophers, t_master *master)
{
	pthread_t		*threads;
	int				i;

	i = -1;
	threads = malloc(sizeof(pthread_t) * (get_psize(philosophers) + 1));
	if (threads == NULL)
		return (ft_error("thread: error.\n"), NULL);
	if (master_thread(threads, get_psize(philosophers), master) != 0)
	{
		free(threads);
		free_philosophers(philosophers, get_psize(philosophers));
		return (NULL);
	}
	while (philosophers[++i])
	{
		if (pthread_create(&threads[i], NULL, proutine, philosophers[i]) != 0)
		{
			free(threads);
			free_philosophers(philosophers, get_psize(philosophers));
			return (NULL);
		}
	}
	return (threads);
}

int	join_threads(pthread_t *threads, t_philosopher **philosophers)
{
	int	i;

	i = -1;
	while (philosophers[++i])
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			free_philosophers(philosophers, get_psize(philosophers));
			return (-1);
		}
	}
	if (pthread_join(threads[i], NULL) != 0)
	{
		free_philosophers(philosophers, get_psize(philosophers));
		return (-1);
	}
	return (0);
}

void	start_threads(t_philosopher **philosophers, int total_eat)
{
	t_master	*master;
	pthread_t	*threads;

	master = malloc(sizeof(t_master));
	if (master == NULL)
		return (ft_error("malloc: error\n"));
	init_master(master, philosophers, total_eat);
	threads = create_threads(philosophers, master);
	if (threads == NULL)
		return (ft_error("thread: error.\n"));
	if (join_threads(threads, philosophers) != 0)
		return (free(master), free(threads), ft_error("thread: error.\n"));
	free(master);
	free(threads);
}
