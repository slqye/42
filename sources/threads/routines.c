/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:23:06 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 15:06:29 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	check_meals(t_master *master)
{
	int	i;

	i = -1;
	if (master->total_eat == -1)
		return (0);
	while (master->philosophers[++i])
	{
		if (master->philosophers[i]->total_eat < master->total_eat)
			return (0);
	}
	return (1);
}

int	mroutine_bis(t_master *master, long long time)
{
	int	i;

	i = -1;
	while (master->philosophers[++i])
	{
		master->philosophers[i]->time = time;
		if (master->philosophers[i]->last_eat \
		+ master->philosophers[i]->time_die < time)
		{
			master->philosophers[i]->is_dead = 1;
			return (1);
		}
	}
	return (0);
}

void	*mroutine(void *arg)
{
	t_master		*master;
	struct timeval	pdated_time;
	long long		time;
	int				is_done;
	int				i;

	master = arg;
	is_done = 0;
	time = 0;
	while (!is_done && !check_meals(master))
	{
		i = -1;
		is_done = mroutine_bis(master, time);
		gettimeofday(&pdated_time, NULL);
		time = (pdated_time.tv_sec * 1000 + pdated_time.tv_usec / 1000) \
		- (master->start_time.tv_sec * 1000 \
		+ master->start_time.tv_usec / 1000);
	}
	set_finish(master->philosophers);
	return (NULL);
}

void	proutine_bis(t_philosopher *philosopher)
{
	secure_print(philosopher, "is eating\n");
	philosopher->last_eat = philosopher->time;
	philosopher->total_eat += 1;
	if (philosopher->to_eat != -1 \
	&& philosopher->total_eat >= philosopher->to_eat)
		philosopher->is_finish = 1;
	usleep(philosopher->time_eat * 1000);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
	secure_print(philosopher, "is sleeping\n");
	usleep(philosopher->time_sleep * 1000);
	secure_print(philosopher, "is thinking\n");
}

void	*proutine(void *arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = arg;
	i = 0;
	while (!philosopher->is_dead && !philosopher->is_finish)
	{
		solver(philosopher, i);
		if (!(philosopher->rfork == philosopher->lfork))
			proutine_bis(philosopher);
		i++;
	}
	if (philosopher->is_dead)
		printf("%d\t%d\tdied\n", philosopher->time, philosopher->id);
	return (NULL);
}
