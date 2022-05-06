/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/06 15:06:15 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void *ft_create_philo(t_philo *data_philo)
{
	long	diff;
	int		isLive;

	isLive = 1;
	while(isLive)
	{
		gettimeofday(&(data_philo->time.end), NULL);
		diff = time_diff(&(data_philo->time.start), &(data_philo->time.end));
		//printf("%ld ms\n", diff);
		if (diff >= data_philo->time_to_die)
		{
			printf("%ld ms:	philo %d meur\n", diff, data_philo->id);
			isLive = 0;
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
		printf("valeur threads %d, %ld\n", i + 1, data->tab_philos[i].id_thread);
		if (ret)
			printf("Error creation thread %d\n", i);
		i++;
	}
}



int main(int argc, char **argv)
{
	//static pthread_mutex_t mutex_stock = PTHREAD_MUTEX_INITIALIZER;
	t_data 	data;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argv);
	ft_create_threads(&data);
	ft_print_time_diff(&data, "creation threads\n");
	


	
	/* Attente de la fin des threads. */
	unsigned int i = 0;
	for (i = 0; i < data.nb; i++)
		pthread_join (data.tab_philos[i].id_thread, NULL);
	return (0);
}