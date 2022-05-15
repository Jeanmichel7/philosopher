/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:58:40 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 00:17:58 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_get_forks(t_philo *data_philo)
{
	int	is_hungre;
	int	prev_eating;
	int	next_eating;
	int	fork_left;
	int	fork_right;

	fork_left = 0;
	fork_right = 0;
	pthread_mutex_lock(&(data_philo->philo_mutex));
	is_hungre = data_philo->is_hungre;
	pthread_mutex_unlock(&(data_philo->philo_mutex));
	pthread_mutex_lock(&(data_philo->prev_philo->philo_mutex));
	prev_eating = data_philo->prev_philo->is_eating;
	pthread_mutex_unlock(&(data_philo->prev_philo->philo_mutex));
	pthread_mutex_lock(&(data_philo->next_philo->philo_mutex));
	next_eating = data_philo->next_philo->is_eating;
	pthread_mutex_unlock(&(data_philo->next_philo->philo_mutex));
	if (is_hungre == 1 && prev_eating != 1)
	{
		pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
		if (data_philo->forks[data_philo->id - 1].is_available == 1)
		{
			data_philo->forks[data_philo->id - 1].is_available = 0;
			ft_print_time_diff_philo(data_philo, "has taken left fork\n");
			data_philo->f_left = 1;
		}
		pthread_mutex_unlock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	}
	if (is_hungre == 1 && next_eating != 1)
	{
		pthread_mutex_lock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
		if (data_philo->forks[data_philo->id % data_philo->tot_forks].is_available == 1)
		{
			data_philo->forks[data_philo->id % data_philo->tot_forks].is_available = 0;
			ft_print_time_diff_philo(data_philo, "has taken right fork\n");
			data_philo->f_right = 1;
		}
		pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	}
	pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	fork_left = data_philo->f_left;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	pthread_mutex_lock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	fork_right = data_philo->f_right;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	if (fork_left && fork_right)
	{
		pthread_mutex_lock(&(data_philo->philo_mutex));
		data_philo->is_hungre = 0;
		data_philo->last_time_eat = ft_print_time_diff_philo(data_philo, \
		"is eating\n");
		data_philo->is_eating = 1;
		data_philo->count_eat += 1;
		pthread_mutex_unlock(&data_philo->philo_mutex);
		return (1);
	}
	return (0);
}

void	ft_drop_forks(t_philo *data_philo)
{
	pthread_mutex_lock(&(data_philo->philo_mutex));
	data_philo->f_left = 0;
	data_philo->f_right = 0;
	data_philo->is_eating = 0;
	pthread_mutex_unlock(&data_philo->philo_mutex);
	pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	data_philo->forks[data_philo->id - 1].is_available = 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	pthread_mutex_lock(&(data_philo->forks[data_philo->id % \
	data_philo->tot_forks].fork_mutex));
	data_philo->forks[data_philo->id % \
	data_philo->tot_forks].is_available = 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id % \
	data_philo->tot_forks].fork_mutex));
	ft_print_time_diff_philo(data_philo, "is sleeping\n");
	usleep(data_philo->time_to_sleep * 1000);
	ft_print_time_diff_philo(data_philo, "is thinking\n");
	pthread_mutex_lock(&(data_philo->philo_mutex));
	data_philo->is_hungre = 1;
	pthread_mutex_unlock(&data_philo->philo_mutex);
}
