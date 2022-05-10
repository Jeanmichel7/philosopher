/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:36:15 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/10 02:26:46 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("Mauvais nombre d'argument\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		printf("argv[%d] : %s\n", i, argv[i]);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("argument \"%s\" non valide\n", argv[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}





/*
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
			data_philo->forkRight = 1;
			forkRight = 1;
		}
		if (data_philo->forkRight == 1)
			forkRight = 1;
		pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
		if (forkLeft && forkRight)
			return (1);
	}
	return (0);
*/

/*
int	ft_get_forks(t_philo *data_philo)
{
	int	forkLeft;
	int	forkRight;

	forkLeft = 0;
	forkRight = 0;
	pthread_mutex_lock(&(data_philo->forks[data_philo->id - 1].fork_mutex));
	if (data_philo->forks[data_philo->id - 1].isAvailable == 1)
	{
		ft_print_time_diff_philo(data_philo, "has taken left fork\n");
		data_philo->forks[data_philo->id - 1].isAvailable = 0;
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
		data_philo->forkRight = 1;
		forkRight = 1;
	}
	if (data_philo->forkRight == 1)
		forkRight = 1;
	pthread_mutex_unlock(&(data_philo->forks[data_philo->id % data_philo->tot_forks].fork_mutex));
	if (forkLeft && forkRight)
		return (1);
	else
		return (0);
}

*/