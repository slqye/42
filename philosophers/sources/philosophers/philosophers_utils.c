/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:30:16 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 12:17:45 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

t_philosopher	*create_philosopher(int id, int argc, char **argv)
{
	t_philosopher	*result;

	result = malloc(sizeof(t_philosopher));
	if (result == NULL)
		return (NULL);
	result->rfork = malloc(sizeof(pthread_mutex_t));
	if (result->rfork == NULL)
		return (free(result), NULL);
	result->id = id;
	result->time_die = ft_atol(argv[2]);
	result->time_eat = ft_atol(argv[3]);
	result->time_sleep = ft_atol(argv[4]);
	result->total_eat = 0;
	result->to_eat = -1;
	result->is_dead = 0;
	result->last_eat = 0;
	result->is_finish = 0;
	result->time = 0;
	if (argc == 6)
		result->to_eat = ft_atol(argv[5]);
	return (result);
}

void	set_finish(t_philosopher	**philosophers)
{
	int	i;

	i = -1;
	while (philosophers[++i])
		philosophers[i]->is_finish = 1;
}

int	f_add_forks(t_philosopher	**philosophers)
{
	int	i;

	i = -1;
	while (philosophers[++i])
	{
		if (pthread_mutex_init(philosophers[i]->rfork, NULL) != 0)
			return (-1);
		if (philosophers[i + 1] != NULL)
			philosophers[i + 1]->lfork = philosophers[i]->rfork;
		else
			philosophers[0]->lfork = philosophers[i]->rfork;
	}
	return (0);
}

int	get_psize(t_philosopher **philosophers)
{
	int	i;

	i = -1;
	while (philosophers[++i])
		;
	return (i);
}

void	free_philosophers(t_philosopher **philosophers, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(philosophers[i]->rfork);
		free(philosophers[i]);
	}
	free(philosophers);
}
