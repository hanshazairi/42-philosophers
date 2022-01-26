/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 01:40:30 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/25 01:40:45 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
		ret = ret * 10 + (*str++ - '0');
	return (ret);
}

int	ft_strncmp(char *str_1, char *str_2, int n)
{
	int	i;

	i = 0;
	while (*str_1 && *str_2 && i < n)
	{
		if (*str_1 != *str_2)
			return (*(unsigned char *)str_1 - *(unsigned char *)str_2);
		++str_1;
		++str_2;
		++i;
	}
	if (i == n)
	{
		--str_1;
		--str_2;
	}
	return (*(unsigned char *)str_1 - *(unsigned char *)str_2);
}

int	ft_strlen(char *s)
{
	int	ret;

	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}

void	ft_usleep(unsigned int n)
{
	long	start_ts;
	long	step_ts;

	start_ts = get_ts();
	while (1)
	{
		step_ts = get_ts();
		if ((step_ts - start_ts) * 1000 >= n)
			break ;
		usleep(500);
	}
}
