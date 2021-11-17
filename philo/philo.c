/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 01:04:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/17 16:50:02 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

static long	get_ts(void)
{
	long			ts;
	struct timeval	s_tv;

	gettimeofday(&s_tv, 0);
	ts = s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000;
	return (ts);
}

static void	*live(void *arg)
{
	int		runs;
	t_philo	*philo;

	philo = (t_philo *)arg;
	runs = 0;
	while (runs++ < 2)
	{
		pthread_mutex_lock(philo->fork_1);
		printf("%ld %d has taken a fork\n", get_ts(), philo->seat);
		pthread_mutex_lock(philo->fork_2);
		printf("%ld %d has taken a fork\n", get_ts(), philo->seat);
		printf("%ld %d is eating\n", get_ts(), philo->seat);
		printf("%ld %d is sleeping\n", get_ts(), philo->seat);
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		usleep(1000);
		printf("%ld %d is thinking\n", get_ts(), philo->seat);
	}
	return (0);
}

static void	pthread_helper(void *f, t_table *table)
{
	int		i;
	int		error;

	i = 0;
	while (i < table->pax)
	{
		if (f == pthread_mutex_init)
			error = ((t_mutex_init)f)(&table->forks[i], 0);
		else if (f == pthread_create)
		{
			table->philos[i].seat = i + 1;
			table->philos[i].fork_1 = &table->forks[i];
			table->philos[i].fork_2 = &table->forks[i + 1];
			if (table->philos[i].seat == table->pax)
			{
				table->philos[i].fork_1 = &table->forks[0];
				table->philos[i].fork_2 = &table->forks[i];
			}
			error = ((t_create)f)(&table->philos[i].philo, 0, live, (void *)&table->philos[i]);
		}
		else if (f == pthread_join)
			error = ((t_join)f)(table->philos[i].philo, 0);
		else if (f == pthread_mutex_destroy)
			error = ((t_mutex_destroy)f)(&table->forks[i]);
		if (error != 0)
			printf("Error\n");
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 2)
	{
		table.pax = ft_atoi(argv[1]);
		table.philos = malloc(sizeof(t_philo) * table.pax);
		if (!table.philos)
		{
			printf("Error\n");
			return (1);
		}
		table.forks = malloc(sizeof(pthread_mutex_t) * table.pax);
		if (!table.forks)
		{
			printf("Error\n");
			free(table.philos);
			return (1);
		}
		pthread_helper(pthread_mutex_init, &table);
		pthread_helper(pthread_create, &table);
		pthread_helper(pthread_join, &table);
		pthread_helper(pthread_mutex_destroy, &table);
		free(table.forks);
		free(table.philos);
	}
	return (0);
}
