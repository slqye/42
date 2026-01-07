/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:00 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/19 15:38:58 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MINT_MAX 2147483647

typedef struct s_philosopher
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				id;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				total_eat;
	int				to_eat;
	int				is_dead;
	int				last_eat;
	int				is_finish;
	int				time;
}	t_philosopher;

typedef struct s_master
{
	t_philosopher	**philosophers;
	struct timeval	start_time;
	int				total_eat;
}	t_master;

void			philosophers(int argc, char **argv);
t_philosopher	*create_philosopher(int id, int argc, char **argv);
int				f_add_forks(t_philosopher	**philosophers);
void			free_philosophers(t_philosopher **philosophers, int size);
void			set_finish(t_philosopher	**philosophers);

void			start_threads(t_philosopher **philosophers, int total_eat);
void			init_master(t_master *master, t_philosopher **philosophers, \
int total_eat);
int				master_thread(pthread_t *threads, int size, t_master *master);
void			*proutine(void *arg);
void			*mroutine(void *arg);
int				get_psize(t_philosopher **philosophers);
void			solver(t_philosopher *philosopher, int i);
void			secure_print(t_philosopher *philosopher, char *str);

long			ft_atol(const char *str);
void			ft_error(char *str);
int				ft_strlen(char *str);

#endif