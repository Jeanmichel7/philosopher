/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:00:55 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 00:14:58 by jrasser          ###   ########.fr       */
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

void	ft_set_philo(t_data *data, int i, char **argv)
{
	gettimeofday(&(data->philos[i].time.start), NULL);
	data->philos[i].time_to_die = ft_atoi(argv[2]);
	data->philos[i].time_to_eat = ft_atoi(argv[3]);
	data->philos[i].time_to_sleep = ft_atoi(argv[4]);
	data->philos[i].f_left = 0;
	data->philos[i].f_right = 0;
	data->philos[i].is_eating = 0;
	data->philos[i].is_hungre = 1;
	data->philos[i].last_time_eat = 0;
	data->philos[i].tot_forks = data->nb;
	data->philos[i].count_eat = 0;
	data->philos[i].is_one_dead = 0;
	data->philos[i].main_mutex = (data->main_mutex);
	pthread_mutex_init(&(data->philos[i].philo_mutex), NULL);
	pthread_mutex_init(&(data->philos[i].print_mutex), NULL);
	data->forks[i].is_available = 1;
	pthread_mutex_init(&(data->forks[i].fork_mutex), NULL);
}

void	ft_sub_set_philo(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb)
	{
		data->philos[i].prev_philo = &(data->philos[i - 1]);
		data->philos[i].next_philo = &(data->philos[i + 1]);
		if (i == 0)
			data->philos[i].prev_philo = &(data->philos[data->nb - 1]);
		if (i == data->nb - 1)
			data->philos[i].next_philo = &(data->philos[0]);
		data->philos[i++].forks = (data->forks);
	}
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
	data.philos = malloc(sizeof(t_philo) * data.nb);
	data.forks = malloc(sizeof(t_forks) * data.nb);
	pthread_mutex_init(&(data.main_mutex), NULL);
	i = 0;
	while (i < data.nb)
	{
		ft_set_philo(&data, i, argv);
		i++;
	}
	ft_sub_set_philo(&data);
	return (data);
}
