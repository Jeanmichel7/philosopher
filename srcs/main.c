/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/06 16:26:01 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_check_isAllAlive(t_data *data)
{
	long			diff;
	unsigned int	i;

	i = 0;
	while (i < data->nb)
	{
		gettimeofday(&(data->tab_philos[i].time.end), NULL);
		diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
		//printf("%ld ms\n", diff);
		if (diff >= data->tab_philos[i].time_to_die)
		{
			gettimeofday(&(data->tab_philos[i].time.end), NULL);
			diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
			printf("%10ld ms:	philo %d meur\n", diff, data->tab_philos[i].id);
			data->tab_philos[i].isAlive = 0;
			return (0);
		}
		i++;
	}
	return (1);
}







static void *ft_create_philo(t_philo *data_philo)
{
	t_time	newTime;
	long	diff;

	data_philo->isAlive = 1;
	
	while(data_philo->isAlive == 1)
	{
		diff = 0;
		gettimeofday(&(newTime.start), NULL);
		ft_print_time_diff_philo(data_philo, "is eating\n");
		while (diff <= data_philo->time_to_eat)
		{
			gettimeofday(&(newTime.end), NULL);
			diff = time_diff(&(newTime.start), &(newTime.end));
		}

		diff = 0;
		gettimeofday(&(newTime.start), NULL);
		ft_print_time_diff_philo(data_philo, "is sleeping\n");

		while (diff <= data_philo->time_to_sleep)
		{
			gettimeofday(&(newTime.end), NULL);
			diff = time_diff(&(newTime.start), &(newTime.end));
		}



		long timeToThink = data_philo->time_to_die - data_philo->time_to_eat - data_philo->time_to_sleep;
		diff = 0;
		gettimeofday(&(newTime.start), NULL);
		ft_print_time_diff_philo(data_philo, "is thinking\n");
		while (diff <= timeToThink)
		{
			gettimeofday(&(newTime.end), NULL);
			diff = time_diff(&(newTime.start), &(newTime.end));
		}
	}


	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int 			ret;
	unsigned int	i;

	i = 0;
	while (i < data->nb)
	{
		data->tab_philos[i].id = i + 1;
		ret = pthread_create(&data->tab_philos[i].id_thread, NULL, (void *)ft_create_philo, &(data->tab_philos[i]));
		//printf("valeur threads %d, %ld\n", i + 1, data->tab_philos[i].id_thread);
		if (ret)
			printf("Error creation thread %d\n", i);
		i++;
	}
}

int main(int argc, char **argv)
{
	//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	t_data 	data;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argv);
	ft_create_threads(&data);

	//ft_print_time_diff(&data, "creation threads\n");
	
	while (ft_check_isAllAlive(&data))
	{
	}
	
	/* Attente de la fin des threads. */
	unsigned int i = 0;
	for (i = 0; i < data.nb; i++)
		pthread_join (data.tab_philos[i].id_thread, NULL);
	return (0);
}