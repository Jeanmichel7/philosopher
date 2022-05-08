/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:00:55 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/08 03:10:27 by jrasser          ###   ########.fr       */
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

t_data	ft_get_args(char **argv)
{
	t_data			data;
	unsigned int	i;

	gettimeofday(&(data.time.start), NULL);
	data.nb = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.tab_time_each_eat = NULL;
	i = 0;
	data.tab_philos = malloc(sizeof(t_philo) * data.nb);
	data.forks = malloc(sizeof(t_forks) * data.nb);
	while (i < data.nb)
	{
		gettimeofday(&(data.tab_philos[i].time.start), NULL);
		data.tab_philos[i].time_to_die = ft_atoi(argv[2]);
		data.tab_philos[i].time_to_eat = ft_atoi(argv[3]);
		data.tab_philos[i].time_to_sleep = ft_atoi(argv[4]);
		data.tab_philos[i].forkLeft = 0;
		data.tab_philos[i].forkRight = 0;
		data.forks[i].pos = i;
		data.forks[i].isAvailable = 1;
		data.forks[i].tot_forks = data.nb;
		data.tab_philos[i].forks = data.forks;
		i++;
	}
	return (data);
}