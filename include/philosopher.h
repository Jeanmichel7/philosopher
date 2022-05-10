/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:25:22 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/10 22:00:05 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_time
{
	struct timeval	start;
	struct timeval	end;
}	t_time;

typedef struct s_forks
{
	int				isAvailable;
	unsigned int	forks_available;
	pthread_mutex_t fork_mutex;

}	t_forks;

typedef struct s_philo
{
	pthread_t		id_thread;
	unsigned int	id;
	int				isAlive;
	t_forks			*forks;
	unsigned int	tot_forks;
	int				forkRight;
	int				forkLeft;
	int				isEating;
	int				isOneDead;
	t_time			time;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			last_time_eat;
	unsigned int	count_eat;
	pthread_mutex_t philo_mutex;
	pthread_mutex_t *main_mutex;
	pthread_mutex_t print_mutex;

}	t_philo;

typedef struct s_data
{
	unsigned int	nb;
	t_philo			*philos;
	t_forks			*forks;
	unsigned int	index;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	x_eat;
	t_time			time;
	pthread_mutex_t main_mutex;
}	t_data;

/* ARGS */
int		ft_check_arg(int argc, char **argv);
t_data	ft_get_args(int argc, char **argv);

/* CHECK ALIVE */
int 	ft_check_isAllAlive(t_data *d);

/*  TIME  */
long	time_diff(struct timeval *start, struct timeval *end);
void	ft_print_time_diff(t_data *data, char *str);
long	ft_print_time_diff_philo(t_philo *data, char *str);

/* FORKS */
int		ft_get_forks(t_philo *data_philo);
void	ft_drop_forks(t_philo *data_philo);

#endif