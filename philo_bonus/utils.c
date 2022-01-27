/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 01:03:56 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/27 11:15:34 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static void	print_status(long ts, t_philo *philo, char *status)
{
	if (!philo->servings)
		return ;
	sem_wait(philo->pen);
	if (!ts)
		ts = get_ts();
	if (!ft_strncmp("is eating", status, ft_strlen(status)))
		philo->last_ate = ts;
	printf("%ld %d %s\n", ts, philo->seat, status);
	if (ft_strncmp("died", status, ft_strlen(status)))
		sem_post(philo->pen);
}

long	get_ts(void)
{
	long			ts;
	struct timeval	s_tv;

	gettimeofday(&s_tv, 0);
	ts = s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000;
	return (ts);
}

void	*die(void *arg)
{
	long	ts;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->servings != 0)
	{
		ts = get_ts();
		if (ts - philo->last_ate > philo->lifespan)
		{
			print_status(ts, philo, "died");
			exit(philo->seat);
		}
		ft_usleep(500);
	}
	return (0);
}

void	*live(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->servings != 0)
	{
		print_status(0, philo, "is thinking");
		sem_wait(philo->forks);
		print_status(0, philo, "has taken a fork");
		sem_wait(philo->forks);
		print_status(0, philo, "has taken a fork");
		print_status(0, philo, "is eating");
		ft_usleep(philo->eat_duration * 1000);
		print_status(0, philo, "is sleeping");
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_usleep(philo->sleep_duration * 1000);
		philo->servings -= 1;
	}
	return (0);
}
