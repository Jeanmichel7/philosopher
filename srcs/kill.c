/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:57:22 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 00:58:35 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_kill_all_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		data->philos[i].is_alive = 0;
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		pthread_mutex_lock(&(data->philos[i].print_mutex));
		data->philos[i].is_one_dead = 1;
		pthread_mutex_unlock(&(data->philos[i].print_mutex));
		i++;
	}
}

void	ft_one_dead(t_data *data, unsigned int limit_eat, long diff, int i)
{
	ft_kill_all_philos(data);
	gettimeofday(&(data->philos[i].time.end), NULL);
	diff = time_diff(&(data->philos[i].time.start),\
	&(data->philos[i].time.end));
	if (limit_eat == data->x_eat)
	{
		printf("%10ld ms:	FIN everyone has eaten %dx\n", diff, \
		data->x_eat);
	}
	else
		printf("%10ld ms:	philo %d died\n", diff, data->philos[i].id);
}

int	ft_check_all_alive(t_data *d)
{
	long			diff;
	long			limit;
	unsigned int	i;
	unsigned int	limit_eat;

	i = 0;
	limit_eat = 0;
	while (i < d->nb)
	{
		pthread_mutex_lock(&(d->philos[i].philo_mutex));
		limit = d->philos[i].last_time_eat + d->philos[i].time_to_die;
		if (d->philos[i].count_eat == d->x_eat && d->x_eat != 0)
			limit_eat += 1;
		pthread_mutex_unlock(&(d->philos[i].philo_mutex));
		gettimeofday(&(d->philos[i].time.end), NULL);
		diff = time_diff(&(d->philos[i].time.start), &(d->philos[i].time.end));
		if (diff > limit || (limit_eat == d->x_eat && d->x_eat != 0))
		{
			ft_one_dead(d, limit_eat, diff, i);
			return (0);
		}
		i++;
	}
	return (1);
}
