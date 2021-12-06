/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 01:04:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/07 02:38:00 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	cleanup(t_table *table, const char *str)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	if (str)
		printf("%s\n", str);
}

static int	init_philo(char **argv, t_table *table, int i)
{
	table->philos[i].seat = i + 1;
	table->philos[i].has_fork_1 = 0;
	table->philos[i].has_fork_2 = 0;
	table->philos[i].lifespan = ft_atoi(argv[1]) * 1000;
	table->philos[i].servings = -1;
	if (argv[4])
		table->philos[i].servings = ft_atoi(argv[4]);
	table->philos[i].eat_duration = ft_atoi(argv[2]) * 1000;
	table->philos[i].sleep_duration = ft_atoi(argv[3]) * 1000;
	table->philos[i].can_eat = &table->is_open;
	table->philos[i].last_ate = get_ts();
	table->philos[i].pen = &table->pen;
	if (table->philos[i].seat == table->pax)
	{
		table->philos[i].fork_1 = &table->forks[0];
		table->philos[i].fork_2 = &table->forks[i];
	}
	else
	{
		table->philos[i].fork_1 = &table->forks[i];
		table->philos[i].fork_2 = &table->forks[i + 1];
	}
	return (1);
}

static int	pthread_helper(char **argv, void *f, t_table *table)
{
	int		i;
	int		error;

	i = -1;
	error = 0;
	while (++i < table->pax)
	{
		if (f == pthread_mutex_init)
			error = ((t_mutex_init)f)(&table->forks[i], 0);
		else if (f == pthread_create && init_philo(argv, table, i))
			error = (((t_create)f)(&table->philos[i].philo_live, 0, live, \
					&table->philos[i]) \
					|| ((t_create)f)(&table->philos[i].philo_die, 0, die, \
					&table->philos[i]));
		else if (f == pthread_join)
			error = (((t_join)f)(table->philos[i].philo_live, 0) \
					|| ((t_join)f)(table->philos[i].philo_die, 0));
		else if (f == pthread_mutex_destroy)
			error = ((t_mutex_destroy)f)(&table->forks[i]);
		if (error)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		table.pax = ft_atoi(argv[1]);
		table.is_open = 1;
		table.philos = malloc(sizeof(t_philo) * table.pax);
		table.forks = malloc(sizeof(pthread_mutex_t) * table.pax);
		if (!table.philos || !table.forks)
		{
			cleanup(&table, "Error: malloc");
			return (1);
		}
		if (pthread_mutex_init(&table.pen, 0) \
				|| pthread_helper(0, pthread_mutex_init, &table) \
				|| pthread_helper(argv + 1, pthread_create, &table) \
				|| pthread_helper(0, pthread_join, &table) \
				|| pthread_helper(0, pthread_mutex_destroy, &table))
		{
			cleanup(&table, "Error: pthread");
			return (1);
		}
		cleanup(&table, 0);
	}
	return (0);
}
