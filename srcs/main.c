/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/10 21:58:49 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void *ft_loop_philo(t_philo *data_philo)
{
	int	isAlive;
	
	pthread_mutex_lock(&(data_philo->philo_mutex));
	data_philo->isAlive = 1;
	isAlive = data_philo->isAlive;
	pthread_mutex_unlock(&data_philo->philo_mutex);
	while (isAlive == 1)
	{
		if (ft_get_forks(data_philo))
		{
			pthread_mutex_lock(&(data_philo->philo_mutex));
			data_philo->last_time_eat = ft_print_time_diff_philo(data_philo, \
			"is eating\n");
			data_philo->count_eat += 1;
			pthread_mutex_unlock(&data_philo->philo_mutex);
			usleep(data_philo->time_to_eat * 1000);
			ft_drop_forks(data_philo);
		}
		pthread_mutex_lock(&(data_philo->philo_mutex));
		isAlive = data_philo->isAlive;
		pthread_mutex_unlock(&data_philo->philo_mutex);
	}
	return (NULL);
}

void ft_create_threads(t_data *data)
{
	int				ret;
	unsigned int	i;

	i = 0;
	while (i < data->nb)
	{
		data->philos[i].id = i + 1;
		ret = pthread_create(&data->philos[i].id_thread, NULL, \
			(void *)ft_loop_philo, &(data->philos[i]));
		if (ret)
			printf("Error creation thread %d\n", i);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data 			data;
	unsigned int	i;
	int				ret;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argc, argv);
	pthread_mutex_init(&(data.main_mutex), NULL);
	ft_create_threads(&data);
	while (1)
	{
		ret = ft_check_isAllAlive(&data);
		if (ret != 1)
		{
			i = 0;
			while (i < data.nb)
			{
				pthread_join(data.philos[i].id_thread, NULL);
				i++;
			}
			free(data.philos);
			free(data.forks);
			return (0);
		}
	}
	return (0);
}
