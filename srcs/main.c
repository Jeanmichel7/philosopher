/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/08 19:26:41 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


void ft_kill_all_philos(t_data *data)
{
	unsigned int i;

	i = 0;
	while (i < data->nb)
	{
	//pthread_mutex_lock(&(data->tab_philos[i].forks->mutex));

		data->tab_philos[i].isAlive = 0;
		//free(data->tab_philos[i].forks);
	//pthread_mutex_unlock(&(data->tab_philos[i].forks->mutex));
		
		i++;
	}
}

int ft_check_isAllAlive(t_data *data)
{
	long 			diff;
	unsigned int 	i;

	i = 0;
	while (i < data->nb)
	{
		gettimeofday(&(data->tab_philos[i].time.end), NULL);
		diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
		if (diff > data->tab_philos[i].last_time_eat + data->tab_philos[i].time_to_die)
		{
			gettimeofday(&(data->tab_philos[i].time.end), NULL);
			diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
			printf("%10ld ms:	philo %d died\n", diff, data->tab_philos[i].id);
			ft_kill_all_philos(data);
			return (0);
		}
	}
	return (1);
}


int	ft_get_forks(t_philo *data_philo)
{
	pthread_mutex_lock(&(data_philo->forks->mutex));
	if (data_philo->forks[data_philo->id - 1].isAvailable == 1
		&& data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable == 1
		&& data_philo->forks->tot_forks > 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken a fork\n");
		data_philo->forks[data_philo->id - 1].isAvailable = 0;
		data_philo->forkLeft = 1;
		ft_print_time_diff_philo(data_philo, "has taken a fork\n");
		data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable = 0;
		data_philo->forkRight = 1;
	}
	pthread_mutex_unlock(&(data_philo->forks->mutex));


	if (data_philo->forkLeft && data_philo->forkRight)
		return (1);
	else
		return (0);
}


void	ft_drop_forks(t_philo *data_philo)
{
	data_philo->forks[data_philo->id - 1].isAvailable = 1;
	data_philo->forkLeft = 0;
	data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable = 1;
	data_philo->forkRight = 0;
	data_philo->isEating = 0;
}


static void *ft_loop_philo(t_philo *data_philo)
{
	pthread_mutex_init(&(data_philo->mutex), NULL);
	pthread_mutex_init(&(data_philo->forks->mutex), NULL);

	data_philo->isAlive = 1;
	pthread_mutex_lock(&(data_philo->mutex));
	while (data_philo->isAlive == 1)
	{
		if (ft_get_forks(data_philo))
		{
			data_philo->last_time_eat = ft_print_time_diff_philo(data_philo, "is eating\n");
			data_philo->isEating = 1;
			usleep(data_philo->time_to_eat * 1000);
			ft_drop_forks(data_philo);
			//pthread_mutex_unlock(&(data_philo->forks->mutex));


			ft_print_time_diff_philo(data_philo, "is sleeping\n");
			usleep(data_philo->time_to_sleep * 1000);

			ft_print_time_diff_philo(data_philo, "is thinking\n");
		}
	}
	pthread_mutex_unlock(&(data_philo->mutex));
	return (NULL);
}

void ft_create_threads(t_data *data)
{
	int				ret;
	unsigned int	i;

	i = 0;
	while (i < data->nb)
	{
		data->tab_philos[i].id = i + 1;
		ret = pthread_create(&data->tab_philos[i].id_thread, NULL, (void *)ft_loop_philo, &(data->tab_philos[i]));
		if (ret)
			printf("Error creation thread %d\n", i);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data 			data;
	unsigned int	i;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argv);
	ft_create_threads(&data);


	while (1)
	{
		if (!ft_check_isAllAlive(&data))
		{
			i = 0;
			while (i < data.nb)
			{
				pthread_join (data.tab_philos[i].id_thread, NULL);
				i++;
			}
			free(data.tab_philos);
			free(data.forks);
			return (0);
		}
	}
	return (0);
}
