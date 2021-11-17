/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:25:52 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/17 16:12:30 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				seat;
	pthread_t		philo;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
}	t_philo;

typedef struct s_table
{
	int				pax;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_table;

typedef int	(*t_mutex_init)(pthread_mutex_t *, const pthread_mutexattr_t *);
typedef int	(*t_create)(pthread_t *, const pthread_attr_t *, \
	void *(*start_routine)(void *), void *);
typedef int	(*t_join)(pthread_t, void **value_ptr);
typedef int	(*t_mutex_destroy)(pthread_mutex_t *);

/* utils.c */
int	ft_atoi(const char *str);

#endif
