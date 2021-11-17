/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:08:10 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/17 18:37:21 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

int	ft_atoi(const char *str)
{
	int	ret;

	ret = 0;
	while (*str)
		ret = ret * 10 + (*str++ - '0');
	return (ret);
}

long	get_ts(void)
{
	long			ts;
	struct timeval	s_tv;

	gettimeofday(&s_tv, 0);
	ts = s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000;
	return (ts);
}
