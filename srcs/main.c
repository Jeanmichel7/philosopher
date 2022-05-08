/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:24:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/08 13:40:26 by jrasser          ###   ########.fr       */
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
	long 			diff;
	unsigned int 	i;

	i = 0;
	while (i < data->nb)
	{
		gettimeofday(&(data->tab_philos[i].time.end), NULL);
		diff = time_diff(&(data->tab_philos[i].time.start), &(data->tab_philos[i].time.end));
		if (diff >= data->tab_philos[i].last_time_eat + data->tab_philos[i].time_to_die)
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
	if (data_philo->forks[data_philo->id - 1].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken the left fork\n");
		data_philo->forks[data_philo->id - 1].isAvailable = 0;
		data_philo->forkLeft = 1;
	}

	if (data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken the right fork\n");
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
	//pthread_mutex_lock(&(data_philo->forks->mutex));

	data_philo->forks[data_philo->id - 1].isAvailable = 1;
	data_philo->forkLeft = 0;
	data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable = 1;
	data_philo->forkRight = 0;
	data_philo->isEating = 0;
}


static void *ft_loop_philo(t_philo *data_philo)
{
	//pthread_mutex_lock(&(data_philo->mutex));
	data_philo->isAlive = 1;
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
		ret = pthread_create(&data->tab_philos[i].id_thread, NULL, (void *)ft_loop_philo, &(data->tab_philos[i]));
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



/*

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

int ft_check_isAllAlive(t_philo *data_philo)
{
	long 			diff;
	unsigned int 	i;


	gettimeofday(&(data_philo->time.end), NULL);
	diff = time_diff(&(data_philo->time.start), &(data_philo->time.end));
	

	if (diff >= data_philo->last_time_eat)
	{
		gettimeofday(&(data_philo->time.end), NULL);
		diff = time_diff(&(data_philo->time.start), &(data_philo->time.end));
		printf("%10ld ms:	philo %d died\n", diff, data_philo->id);
		//ft_kill_all_philos(data);
		return (0);
	}

	return (1);
}



/*
int	ft_as_time_to_eat(t_philo *data_philo)
{
	t_time	newTime;
	long	diff;

	gettimeofday(&(newTime.start), NULL);
	newTime.end.tv_sec = newTime.start.tv_sec;
	newTime.end.tv_usec = newTime.start.tv_usec + (data_philo->time_to_eat * 1000);

	diff = time_diff(&(newTime.start), &(newTime.end));
	printf("test diff : %ld\n", diff);
	printf("last eat : %ld\n", data_philo->last_time_eat);

	return (1);
}


int	ft_get_forks(t_philo *data_philo)
{
	pthread_mutex_lock(&(data_philo->forks->mutex));
	if (data_philo->forks[data_philo->id - 1].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken the left fork\n");
		data_philo->forks[data_philo->id - 1].isAvailable = 0;
		data_philo->forkLeft = 1;
	}

	if (data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken the right fork\n");
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
	//pthread_mutex_lock(&(data_philo->forks->mutex));

	data_philo->forks[data_philo->id - 1].isAvailable = 1;
	data_philo->forkLeft = 0;
	data_philo->forks[data_philo->id % data_philo->forks->tot_forks].isAvailable = 1;
	data_philo->forkRight = 0;
	data_philo->isEating = 0;
}


static void *ft_loop_philo(t_philo *data_philo)
{
	//pthread_mutex_lock(&(data_philo->mutex));
	data_philo->isAlive = 1;
	while (ft_check_isAllAlive(data_philo))
	{
		if (ft_get_forks(data_philo))
		{
			data_philo->last_time_eat = ft_print_time_diff_philo(data_philo, "is eating\n");
			//gettimeofday(&(data_philo->time.start), NULL);
			data_philo->isEating = 1;
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
		ret = pthread_create(&data->tab_philos[i].id_thread, NULL, (void *)ft_loop_philo, &(data->tab_philos[i]));
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

/*
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

*/