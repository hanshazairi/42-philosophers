/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 01:44:42 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/07 02:43:11 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

static void	print_status(long ts, t_philo *philo, char *status)
{
	if (!*philo->can_eat)
		return ;
	pthread_mutex_lock(philo->pen);
	if (!ts)
		ts = get_ts();
	if (!ft_strncmp("is eating", status, ft_strlen(status)))
		philo->last_ate = ts;
	else if (!ft_strncmp("has taken a fork", status, ft_strlen(status)))
	{
		if (!philo->has_fork_1)
			++philo->has_fork_1;
		else
			++philo->has_fork_2;
	}
	else if (!ft_strncmp("is sleeping", status, ft_strlen(status)))
	{
		philo->has_fork_1 = 0;
		philo->has_fork_2 = 0;
	}
	if (*philo->can_eat)
		printf("%ld %d %s\n", ts, philo->seat, status);
	pthread_mutex_unlock(philo->pen);
}

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
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->can_eat && philo->servings != 0)
	{
		philo->servings -= 1;
		print_status(0, philo, "is thinking");
		pthread_mutex_lock(philo->fork_1);
		print_status(0, philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_2);
		print_status(0, philo, "has taken a fork");
		print_status(0, philo, "is eating");
		usleep(philo->eat_duration);
		print_status(0, philo, "is sleeping");
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		usleep(philo->sleep_duration);
	}
	return (0);
}

void	*die(void *arg)
{
	long	ts;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->can_eat && philo->servings != 0)
	{
		ts = get_ts();
		if (ts - philo->last_ate > philo->lifespan / 1000)
		{
			print_status(ts, philo, "died");
			*philo->can_eat = 0;
			break ;
		}
		usleep(philo->lifespan);
	}
	if (philo->has_fork_1)
		pthread_mutex_unlock(philo->fork_1);
	if (philo->has_fork_2)
		pthread_mutex_unlock(philo->fork_2);
	return (0);
}
