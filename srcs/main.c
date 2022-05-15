/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 00:17:57 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	*ft_loop_philo(t_philo *data_philo)
{
	int	is_alive;

	pthread_mutex_lock(&(data_philo->philo_mutex));
	data_philo->is_alive = 1;
	if (data_philo->id % 2 == 0)
		usleep(1000);
	is_alive = data_philo->is_alive;
	pthread_mutex_unlock(&data_philo->philo_mutex);
	while (is_alive == 1)
	{
		if (ft_get_forks(data_philo))
		{
			usleep(data_philo->time_to_eat * 1000);
			ft_drop_forks(data_philo);
		}
		pthread_mutex_lock(&(data_philo->philo_mutex));
		is_alive = data_philo->is_alive;
		pthread_mutex_unlock(&data_philo->philo_mutex);
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
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

int	main(int argc, char **argv)
{
	t_data			data;
	unsigned int	i;
	int				ret;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argc, argv);
	ft_create_threads(&data);
	while (1)
	{
		ret = ft_check_all_alive(&data);
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
