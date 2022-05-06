/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/06 13:52:26 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void *ft_update_philo(t_data *data)
{
	long	diff;
	int		isLive;

	isLive = 1;
	while(isLive)
	{
		gettimeofday(&(data->time.end), NULL);
		diff = time_diff(&(data->time.start), &data->time.end);
		//printf("diff:  %ld\n", diff);
		if (diff >= data->time_to_die)
		{
			printf("%ld ms:	philo %d meur\n", diff, data->philo.id);
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
		data->philo.id = i + 1;
		ret = pthread_create(&data->tab_thread_philos[i], NULL, (void *)ft_update_philo, data);
		if (ret)
			printf("Error creation thread %d\n", i);
		i++;
	}
}

int main(int argc, char **argv)
{
	//static pthread_mutex_t mutex_stock = PTHREAD_MUTEX_INITIALIZER;
	t_data 	data;
	long	diff;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argv);
	ft_create_threads(&data);
	

	gettimeofday(&(data.time.end), NULL);
	diff = time_diff(&(data.time.start), &(data.time.end));
	printf("threads créé %ld ms\n\n", diff);
	


	
	/* Attente de la fin des threads. */
	unsigned int i = 0;
	for (i = 0; i < data.nb; i++)
		pthread_join (data.tab_thread_philos[i], NULL);
	return (0);
}