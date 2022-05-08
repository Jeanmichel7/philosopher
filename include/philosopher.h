/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:25:22 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/08 15:23:23 by jrasser          ###   ########.fr       */
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

#include <errno.h>

typedef struct s_time
{
	struct timeval	start;
	struct timeval	end;
}	t_time;

typedef struct s_forks
{
	unsigned int	pos;
	int				isAvailable;
	unsigned int	tot_forks;
	pthread_mutex_t mutex;

}	t_forks;

typedef struct s_philo
{
	pthread_t		id_thread;
	unsigned int	id;
	int				isAlive;
	t_forks			*forks;
	int				forkRight;
	int				forkLeft;
	int				isEating;
	t_time			time;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			last_time_eat;
	pthread_mutex_t mutex;

}	t_philo;

typedef struct s_data
{
	unsigned int	nb;
	t_philo			*tab_philos;
	t_forks			*forks;
	unsigned int	index;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	*tab_time_each_eat;
	t_time			time;
}	t_data;

/*
typedef struct s_datas
{
	t_data			data;
	unsigned int	index;
}	t_datas;
*/


int			ft_check_arg(int argc, char **argv);
t_data		ft_get_args(char **argv);


/*  TIME  */
long	time_diff(struct timeval *start, struct timeval *end);
void	ft_print_time_diff(t_data *data, char *str);
long	ft_print_time_diff_philo(t_philo *data, char *str);

#endif