/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 01:04:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/17 02:10:09 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define PHILOS 5

pthread_t		g_philos[PHILOS];
pthread_mutex_t	g_forks[PHILOS];

long	get_ts(void)
{
	long			ts;
	struct timeval	s_tv;

	gettimeofday(&s_tv, 0);
	ts = s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000;
	return (ts);
}

void	*live(void *arg)
{
	int				i;
	int				x;
	pthread_mutex_t	fork_1;
	pthread_mutex_t	fork_2;

	i = (size_t)arg;
	x = 0;
	if (i != PHILOS - 1)
	{
		fork_1 = g_forks[i];
		fork_2 = g_forks[i + 1];
	}
	else
	{
		fork_1 = g_forks[0];
		fork_2 = g_forks[i];
	}
	while (x++ < 2)
	{
		pthread_mutex_lock(&fork_1);
		printf("%ld %d has taken a fork\n", get_ts(), i + 1);
		pthread_mutex_lock(&fork_2);
		printf("%ld %d has taken a fork\n", get_ts(), i + 1);
		printf("%ld %d is eating\n", get_ts(), i + 1);
		printf("%ld %d is sleeping\n", get_ts(), i + 1);
		pthread_mutex_unlock(&fork_1);
		pthread_mutex_unlock(&fork_2);
		usleep(1000);
		printf("%ld %d is thinking\n", get_ts(), i + 1);
	}
	return (0);
}

int	main(void)
{
	int	i;

	i = 0;
	get_ts();
	while (i < PHILOS)
	{
		if (pthread_mutex_init(&g_forks[i++], 0) != 0)
		{
			printf("Error\n");
			return (1);
		}
	}
	i = 0;
	while (i < PHILOS)
	{
		if (pthread_create(&g_philos[i], 0, live, (void *)(size_t)i) != 0)
		{
			printf("Error\n");
			return (2);
		}
		++i;
	}
	i = 0;
	while (i < PHILOS)
	{
		if (pthread_join(g_philos[i++], 0) != 0)
		{
			printf("Error\n");
			return (3);
		}
	}
	i = 0;
	while (i < PHILOS)
	{
		if (pthread_mutex_destroy(&g_forks[i++]) != 0)
		{
			printf("Error\n");
			return (4);
		}
	}
	return (0);
}
