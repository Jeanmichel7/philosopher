/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/10 03:36:46 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void ft_kill_all_philos(t_data *data)
{
	unsigned int i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->tab_philos[i].philo_mutex);
		data->tab_philos[i].isAlive = 0;
		pthread_mutex_unlock(&data->tab_philos[i].philo_mutex);
		i++;
	}
}

int ft_check_isAllAlive(t_data *data)
{
	long 			diff;
	long			limit;
	unsigned int 	i;
	unsigned int	limit_eat;

	i = 0;
	limit_eat = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&(data->tab_philos[i].philo_mutex));
		limit = data->tab_philos[i].last_time_eat + data->tab_philos[i].time_to_die;
		if (data->tab_philos[i].count_eat == data->each_must_eat)
			limit_eat += 1;
		pthread_mutex_unlock(&(data->tab_philos[i].philo_mutex));
		gettimeofday(&(data->tab_philos[i].time.end), NULL);
		diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
		if (diff > limit || limit_eat == data->nb)
		{
			if (limit_eat == data->nb)
			{
				usleep(data->tab_philos[i].time_to_eat * 1000);
				gettimeofday(&(data->tab_philos[i].time.end), NULL);
				diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
				printf("%10ld ms:	FIN\n		everyone has eaten %dx\n", diff, data->each_must_eat);
			}
			else
				printf("%10ld ms:	philo %d died\n", diff, data->tab_philos[i].id);
			ft_kill_all_philos(data);
			return (0);
		}
		i++;
	}
	return (1);
}



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
	pthread_mutex_lock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	data_philo->forks[data_philo->id % data_philo->tot_forks].isAvailable = 1;
	//data_philo->forks[data_philo->id % data_philo->tot_forks].forks_available += 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	ft_print_time_diff_philo(data_philo, "is sleeping\n");
	usleep(data_philo->time_to_sleep * 1000);
	ft_print_time_diff_philo(data_philo, "is thinking\n");
}

static void *ft_loop_philo(t_philo *data_philo)
{
	pthread_mutex_lock(&(data_philo->philo_mutex));
	data_philo->isAlive = 1;
	int isAlive;
	isAlive = data_philo->isAlive;
	pthread_mutex_unlock(&data_philo->philo_mutex);
	while (isAlive == 1)
	{
		if (ft_get_forks(data_philo))
		{
			pthread_mutex_lock(&(data_philo->philo_mutex));
			data_philo->last_time_eat = ft_print_time_diff_philo(data_philo, "is eating\n");
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
				pthread_join(data.tab_philos[i].id_thread, NULL);
				i++;
			}
			free(data.tab_philos);
			free(data.forks);
			return (0);
		}
	}
	return (0);
}
