/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:25:52 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/07 02:56:05 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				seat;
	int				has_fork_1;
	int				has_fork_2;
	int				lifespan;
	int				servings;
	int				eat_duration;
	int				sleep_duration;
	int				*can_eat;
	long			last_ate;
	pthread_t		philo_die;
	pthread_t		philo_live;
	pthread_mutex_t	*pen;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
}	t_philo;

typedef struct s_table
{
	int				pax;
	int				is_open;
	t_philo			*philos;
	pthread_mutex_t	pen;
	pthread_mutex_t	*forks;
}	t_table;

typedef int	(*t_mutex_init)(pthread_mutex_t *, const pthread_mutexattr_t *);
typedef int	(*t_create)(pthread_t *, const pthread_attr_t *, \
	void *(*start_routine)(void *), void *);
typedef int	(*t_join)(pthread_t, void **value_ptr);
typedef int	(*t_mutex_destroy)(pthread_mutex_t *);

/* utils.c */
long	get_ts(void);
void	*live(void *arg);
void	*die(void *arg);

/* libft_utils.c */
int		ft_atoi(char *str);
int		ft_strncmp(char *str_1, char *str_2, int n);
int		ft_strlen(char *s);
void	ft_usleep(unsigned int n);

#endif
