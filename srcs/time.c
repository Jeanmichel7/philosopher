/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 23:16:25 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/06 16:27:17 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long	time_diff(struct timeval *start, struct timeval *end)
{

	long diff;

	//ret = (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
	//ret = end->tv_usec - start->tv_usec;
	diff = ((end->tv_sec * 1000000 + end->tv_usec) -
    (start->tv_sec * 1000000 + start->tv_usec)) / 1000;
	if (diff == -1)
	{
		printf("%d\n",errno);
		return (0);
	}

	return (diff);
}

void	ft_print_time_diff(t_data *data, char *str)
{
	long diff;

	gettimeofday(&(data->time.end), NULL);
	diff = time_diff(&(data->time.start), &(data->time.end));
	printf("%10ld ms:	%s", diff, str);
}

void	ft_print_time_diff_philo(t_philo *data, char *str)
{
	long diff;

	gettimeofday(&(data->time.end), NULL);
	diff = time_diff(&(data->time.start), &(data->time.end));
	printf("%10ld ms:	philo %d %s", diff, data->id, str);
}