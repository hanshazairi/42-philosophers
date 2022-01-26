/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 23:56:07 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/26 15:38:29 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	int			seat;
	int			lifespan;
	int			servings;
	int			eat_duration;
	int			sleep_duration;
	long		last_ate;
	sem_t		*pen;
	sem_t		*forks;
	pthread_t	philo_die;
	pthread_t	philo_live;
}	t_philo;

typedef struct s_table
{
	int		pax;
	sem_t	*pen;
	sem_t	*forks;
	t_philo	*philos;
}	t_table;

/* utils.c */
long	get_ts(void);
void	*die(void *arg);
void	*live(void *arg);

/* libft_utils.c */
int		ft_atoi(char *str);
int		ft_strlen(char *s);
int		ft_strncmp(char *str_1, char *str_2, int n);
void	ft_usleep(unsigned int n);

#endif
