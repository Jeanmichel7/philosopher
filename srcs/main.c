/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/08 03:51:49 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void ft_kill_all_philos(t_data *data)
{
	unsigned int i;

	i = 0;
	while (i < data->nb)
	{
		data->tab_philos[i].isAlive = 0;
		i++;
	}
}

int ft_check_isAllAlive(t_data *data)
{
	long diff;
	unsigned int i;

	i = 0;
	while (i < data->nb)
	{
		gettimeofday(&(data->tab_philos[i].time.end), NULL);
		diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
		// printf("%ld ms\n", diff);
		if (diff >= data->tab_philos[i].time_to_die)
		{
			gettimeofday(&(data->tab_philos[i].time.end), NULL);
			diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
			printf("%10ld ms:	philo %d died\n", diff, data->tab_philos[i].id);

			ft_kill_all_philos(data);
			return (0);
		}
		i++;
	}
	return (1);
}




int	ft_as_time_to_eat(t_philo *data_philo)
{
/*
	t_time	time;
	long	diff;
	long	now;
	long	limit;
*/

	//gettimeofday(&(time.start), NULL);
	//printf("time start: %ld sec %ld mms\n", time.start.tv_sec, time.start.tv_usec);
	//diff = time_diff(&(time.start), time.start.tv_usec + data_philo->time_to_eat * 1000);
	//printf("diff : %lu ms\n", diff);

	return (1);
}

int	ft_get_forks(t_philo *data_philo)
{
	pthread_mutex_lock(&(data_philo->forks->mutex));
	//printf("philo %d pos fork left : %d, right : %d\n",data_philo->id, pos_fork_left, pos_fork_right);
	//printf("philo %d fork left : %d, right : %d\n",data_philo->id, data_philo->forkLeft, data_philo->forkRight);

	if (data_philo->forks[data_philo->id - 1].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken a left fork\n");
		data_philo->forks[data_philo->id - 1].isAvailable = 0;
		data_philo->forkLeft = 1;
	}

	if (data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken a right fork\n");
		data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable = 0;
		data_philo->forkRight = 1;
	}
	pthread_mutex_unlock(&(data_philo->forks->mutex));


	if (data_philo->forkLeft && data_philo->forkRight
		&& ft_as_time_to_eat(data_philo))
	{
		return (1);
	}
	else
		return (0);
}


void	ft_drop_forks(t_philo *data_philo)
{
	//pthread_mutex_lock(&(data_philo->forks->mutex));

	data_philo->forks[data_philo->id - 1].isAvailable = 1;
	data_philo->forkLeft = 0;
	data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable = 1;
	data_philo->forkRight = 0;
}


static void *ft_create_philo(t_philo *data_philo)
{
	//pthread_mutex_lock(&(data_philo->mutex));
	data_philo->isAlive = 1;
	while (data_philo->isAlive == 1)
	{
		if (ft_get_forks(data_philo))
		{
			data_philo->last_time_eat = ft_print_time_diff_philo(data_philo, "is eating\n");
			usleep(data_philo->time_to_eat * 1000);
			ft_drop_forks(data_philo);
			//pthread_mutex_unlock(&(data_philo->forks->mutex));


			
			ft_print_time_diff_philo(data_philo, "is sleeping\n");
			usleep(data_philo->time_to_sleep * 1000);

			ft_print_time_diff_philo(data_philo, "is thinking\n");
		}
	}
	//pthread_mutex_unlock(&(data_philo->mutex));
	return (NULL);
}

void ft_create_threads(t_data *data)
{
	int ret;
	unsigned int i;


	i = 0;
	while (i < data->nb)
	{
		data->tab_philos[i].id = i + 1;
		ret = pthread_create(&data->tab_philos[i].id_thread, NULL, (void *)ft_create_philo, &(data->tab_philos[i]));
		if (ret)
			printf("Error creation thread %d\n", i);
		i++;
	}
}

int main(int argc, char **argv)
{

	t_data data;

	if (ft_check_arg(argc, argv))
		return (0);
	data = ft_get_args(argv);
	ft_create_threads(&data);

	while (1)
	{
		if (!ft_check_isAllAlive(&data))
			return (0);
	}
	
	unsigned int i = 0;
	for (i = 0; i < data.nb; i++)
		pthread_join (data.tab_philos[i].id_thread, NULL);
	return (0);
}
