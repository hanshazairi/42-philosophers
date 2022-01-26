/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 23:55:39 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/26 13:23:02 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

static void	init_philo(char **argv, t_table *table, int i)
{
	table->philos[i].seat = i + 1;
	table->philos[i].lifespan = ft_atoi(argv[1]);
	table->philos[i].servings = -1;
	if (argv[4])
		table->philos[i].servings = ft_atoi(argv[4]);
	table->philos[i].eat_duration = ft_atoi(argv[2]);
	table->philos[i].sleep_duration = ft_atoi(argv[3]);
	table->philos[i].last_ate = get_ts();
	table->philos[i].forks = table->forks;
	table->philos[i].pen = table->pen;
}

static void	waiter(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	while (++i < table->pax)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
			return ;
	}
	return ;
}

static int	helper(char **argv, t_table *table)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < table->pax)
	{
		init_philo(argv, table, i);
		pid = fork();
		if (!pid)
		{
			if (pthread_create(&table->philos[i].philo_live, 0, live, \
					&table->philos[i]) \
					|| pthread_create(&table->philos[i].philo_die, 0, die, \
					&table->philos[i]) \
					|| pthread_join(table->philos[i].philo_live, 0) \
					|| pthread_join(table->philos[i].philo_die, 0))
				return (1);
			exit(0);
		}
		else if (pid < 0)
			return (1);
	}
	waiter(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		table.pax = ft_atoi(argv[1]);
		table.philos = malloc(sizeof(t_philo) * table.pax);
		if (!table.philos)
			return (1);
		sem_unlink("forks");
		sem_unlink("pen");
		table.forks = sem_open("forks", O_CREAT, S_IRWXU, table.pax);
		table.pen = sem_open("pen", O_CREAT, S_IRWXU, 1);
		if (table.forks == SEM_FAILED || table.pen == SEM_FAILED \
				|| helper(argv + 1, &table))
		{
			free(table.philos);
			return (1);
		}
		sem_close(table.pen);
		sem_close(table.forks);
		sem_unlink("pen");
		sem_unlink("forks");
		free(table.philos);
	}
	return (0);
}
