/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:58:40 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 18:15:51 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_init(t_philo *d_philo, int *is_h, int *prev_eating, int *next_eating)
{
	pthread_mutex_lock(&(d_philo->philo_mutex));
	*is_h = d_philo->is_hungre;
	pthread_mutex_unlock(&(d_philo->philo_mutex));
	pthread_mutex_lock(&(d_philo->prev_philo->philo_mutex));
	*prev_eating = d_philo->prev_philo->is_eating;
	pthread_mutex_unlock(&(d_philo->prev_philo->philo_mutex));
	pthread_mutex_lock(&(d_philo->next_philo->philo_mutex));
	*next_eating = d_philo->next_philo->is_eating;
	pthread_mutex_unlock(&(d_philo->next_philo->philo_mutex));
}

void	ft_bring_fork(t_philo *d_philo, int is_h, int prev_e, int next_e)
{
	if (is_h == 1 && prev_e != 1 && next_e != 1)
	{
		pthread_mutex_lock(&(d_philo->forks[d_philo->id - 1].f_mutex));
		if (d_philo->forks[d_philo->id - 1].is_available == 1)
		{
			d_philo->forks[d_philo->id - 1].is_available = 0;
			ft_print_time_diff_philo(d_philo, "has taken left fork\n");
			d_philo->f_left = 1;
		}
		pthread_mutex_unlock(&(d_philo->forks[d_philo->id - 1].f_mutex));
	}
	if (is_h == 1 && prev_e != 1 && next_e != 1)
	{
		pthread_mutex_lock(&(d_philo->forks[d_philo->id % \
		d_philo->tot_forks].f_mutex));
		if (d_philo->forks[d_philo->id % d_philo->tot_forks].is_available == 1)
		{
			d_philo->forks[d_philo->id % d_philo->tot_forks].is_available = 0;
			ft_print_time_diff_philo(d_philo, "has taken right fork\n");
			d_philo->f_right = 1;
		}
		pthread_mutex_unlock(&(d_philo->forks[d_philo->id % \
		d_philo->tot_forks].f_mutex));
	}
}

void	modif_philo(t_philo *d_philo)
{
	pthread_mutex_lock(&(d_philo->philo_mutex));
	d_philo->is_hungre = 0;
	d_philo->last_time_eat = ft_print_time_diff_philo(d_philo, \
	"is eating\n");
	d_philo->is_eating = 1;
	d_philo->count_eat += 1;
	pthread_mutex_unlock(&d_philo->philo_mutex);
}

int	ft_get_forks(t_philo *d_philo)
{
	int	is_hungre;
	int	prev_eating;
	int	next_eating;
	int	fork_left;
	int	fork_right;

	fork_left = 0;
	fork_right = 0;
	ft_init(d_philo, &is_hungre, &prev_eating, &next_eating);
	ft_bring_fork(d_philo, is_hungre, prev_eating, next_eating);
	pthread_mutex_lock(&(d_philo->forks[d_philo->id - 1].f_mutex));
	fork_left = d_philo->f_left;
	pthread_mutex_unlock(&(d_philo->forks[d_philo->id - 1].f_mutex));
	pthread_mutex_lock(&(d_philo->forks[d_philo->id % \
	d_philo->tot_forks].f_mutex));
	fork_right = d_philo->f_right;
	pthread_mutex_unlock(&(d_philo->forks[d_philo->id % \
	d_philo->tot_forks].f_mutex));
	if (fork_left && fork_right)
	{
		modif_philo(d_philo);
		return (1);
	}
	return (0);
}

void	ft_drop_forks(t_philo *d_philo)
{
	pthread_mutex_lock(&(d_philo->philo_mutex));
	d_philo->f_left = 0;
	d_philo->f_right = 0;
	d_philo->is_eating = 0;
	pthread_mutex_unlock(&d_philo->philo_mutex);
	pthread_mutex_lock(&(d_philo->forks[d_philo->id - 1].f_mutex));
	d_philo->forks[d_philo->id - 1].is_available = 1;
	pthread_mutex_unlock(&(d_philo->forks[d_philo->id - 1].f_mutex));
	pthread_mutex_lock(&(d_philo->forks[d_philo->id % \
	d_philo->tot_forks].f_mutex));
	d_philo->forks[d_philo->id % \
	d_philo->tot_forks].is_available = 1;
	pthread_mutex_unlock(&(d_philo->forks[d_philo->id % \
	d_philo->tot_forks].f_mutex));
	ft_print_time_diff_philo(d_philo, "is sleeping\n");
	ft_better_usleep(d_philo->time_to_sleep * 1000);
	ft_print_time_diff_philo(d_philo, "is thinking\n");
	pthread_mutex_lock(&(d_philo->philo_mutex));
	d_philo->is_hungre = 1;
	pthread_mutex_unlock(&d_philo->philo_mutex);
}
