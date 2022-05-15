/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 23:16:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 00:15:25 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long	time_diff(struct timeval *start, struct timeval *end)
{
	long	diff;

	diff = ((end->tv_sec * 1000000 + end->tv_usec) - \
	(start->tv_sec * 1000000 + start->tv_usec)) / 1000;
	return (diff);
}

void	ft_print_time_diff(t_data *data, char *str)
{
	long	diff;

	gettimeofday(&(data->time.end), NULL);
	diff = time_diff(&(data->time.start), &(data->time.end));
	printf("%10ld ms:	%s", diff, str);
}

long	ft_print_time_diff_philo(t_philo *data, char *str)
{
	long	diff;

	pthread_mutex_lock(&(data->print_mutex));
	if (data->is_one_dead != 1)
	{
		gettimeofday(&(data->time.end), NULL);
		diff = time_diff(&(data->time.start), &(data->time.end));
		printf("%10ld ms:	philo %.2d %s", diff, data->id, str);
		pthread_mutex_unlock(&(data->print_mutex));
		return (diff);
	}
	else
		pthread_mutex_unlock(&(data->print_mutex));
	return (0);
}

void	better_sleep(unsigned int time)
{
	unsigned int	i;

	i = 0;
	while (i < time / 10)
	{
		usleep(10);
		i++;
	}
}
