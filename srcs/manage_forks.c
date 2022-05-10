/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:58:40 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/10 21:58:53 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_get_forks(t_philo *data_philo)
{
	int	forkLeft;
	int	forkRight;
	int	forkLeftAvailable;
	int	forkRightAvailable;

	forkLeft = 0;
	forkRight = 0;
	forkLeftAvailable = 0;
	forkRightAvailable = 0;

	pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	if (data_philo->forks[data_philo->id - 1].isAvailable == 1)
		forkLeftAvailable = 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	pthread_mutex_lock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	if (data_philo->forks[data_philo->id % data_philo->tot_forks].isAvailable == 1)
		forkRightAvailable = 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	if ((forkLeftAvailable && forkRightAvailable))
	{
		pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
		if (data_philo->forks[data_philo->id - 1].isAvailable == 1)
		{
			ft_print_time_diff_philo(data_philo, "has taken left fork\n");
			data_philo->forks[data_philo->id - 1].isAvailable = 0;
			//data_philo->forks[data_philo->id - 1].forks_available -= 1;
			data_philo->forkLeft = 1;
		}
		if (data_philo->forkLeft == 1)
			forkLeft = 1;
		pthread_mutex_unlock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
		pthread_mutex_lock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
		if (data_philo->forks[data_philo->id % data_philo->tot_forks].isAvailable == 1)
		{
			ft_print_time_diff_philo(data_philo, "has taken right fork\n");
			data_philo->forks[data_philo->id % data_philo->tot_forks].isAvailable = 0;
			//data_philo->forks[data_philo->id % data_philo->tot_forks].forks_available -= 1;
			data_philo->forkRight = 1;
		}
		if (data_philo->forkRight == 1)
			forkRight = 1;
		pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
		if (forkLeft && forkRight)
			return (1);
	}
	return (0);
}


void	ft_drop_forks(t_philo *data_philo)
{
	pthread_mutex_lock(&(data_philo->philo_mutex));
	data_philo->forkLeft = 0;
	data_philo->forkRight = 0;
	pthread_mutex_unlock(&data_philo->philo_mutex);
	pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	data_philo->forks[data_philo->id - 1].isAvailable = 1;
	//data_philo->forks[data_philo->id - 1].forks_available += 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	pthread_mutex_lock(&(data_philo->forks[data_philo->id % \
	data_philo->tot_forks].fork_mutex));
	data_philo->forks[data_philo->id % \
	data_philo->tot_forks].isAvailable = 1;
	//data_philo->forks[data_philo->id % data_philo->tot_forks].forks_available += 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id % \
	data_philo->tot_forks].fork_mutex));
	ft_print_time_diff_philo(data_philo, "is sleeping\n");
	usleep(data_philo->time_to_sleep * 1000);
	ft_print_time_diff_philo(data_philo, "is thinking\n");
}
