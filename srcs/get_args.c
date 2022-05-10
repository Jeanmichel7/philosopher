/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:00:55 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/10 21:56:47 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		i;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	res *= sign;
	return ((int)res);
}

void	ft_sub_get_args(t_data *data, int i, char **argv)
{
	gettimeofday(&(data->philos[i].time.start), NULL);
	data->philos[i].time_to_die = ft_atoi(argv[2]);
	data->philos[i].time_to_eat = ft_atoi(argv[3]);
	data->philos[i].time_to_sleep = ft_atoi(argv[4]);
	data->philos[i].forkLeft = 0;
	data->philos[i].forkRight = 0;
	data->philos[i].isEating = 0;
	data->philos[i].last_time_eat = 0;
	data->philos[i].main_mutex = &(data->main_mutex);
	data->philos[i].tot_forks = data->nb;
	data->philos[i].count_eat = 0;
	data->philos[i].isOneDead = 0;
	pthread_mutex_init(&(data->philos[i].philo_mutex), NULL);
	pthread_mutex_init(&(data->philos[i].print_mutex), NULL);
	data->forks[i].isAvailable = 1;
	pthread_mutex_init(&(data->forks[i].fork_mutex), NULL);
}

t_data	ft_get_args(int argc, char **argv)
{
	t_data			data;
	unsigned int	i;

	gettimeofday(&(data.time.start), NULL);
	data.nb = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.x_eat = 0;
	if (argc == 6)
		data.x_eat = ft_atoi(argv[5]);
	i = 0;
	data.philos = malloc(sizeof(t_philo) * data.nb);
	data.forks = malloc(sizeof(t_forks) * data.nb);
	data.forks->forks_available = data.nb;
	while (i < data.nb)
	{
		ft_sub_get_args(&data, i, argv);
		i++;
	}
	i = 0;
	while(i < data.nb)
		data.philos[i++].forks = (data.forks);
	return (data);
}