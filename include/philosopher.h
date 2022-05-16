/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:25:22 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/16 17:05:37 by jrasser          ###   ########.fr       */
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
	int				is_available;
	pthread_mutex_t	f_mutex;

}	t_forks;

typedef struct s_philo
{
	pthread_t		id_thread;
	unsigned int	id;
	int				is_alive;
	t_forks			*forks;
	unsigned int	tot_forks;
	int				f_right;
	int				f_left;
	int				is_eating;
	int				is_hungre;
	int				is_one_dead;
	t_time			time;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			last_time_eat;
	unsigned int	count_eat;
	unsigned int	count_check;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	print_mutex;

	struct s_philo	*prev_philo;
	struct s_philo	*next_philo;
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
	pthread_mutex_t	main_mutex;
}	t_data;

/* ARGS */
int		ft_check_arg(int argc, char **argv);
t_data	ft_get_args(int argc, char **argv);

/* CHECK ALIVE */
int		ft_check_all_alive(t_data *d);

/*  TIME  */
long	time_diff(struct timeval *start, struct timeval *end);
void	ft_print_time_diff(t_data *data, char *str);
long	ft_print_time_diff_philo(t_philo *data, char *str);
void	ft_better_usleep(long time);

/* FORKS */
int		ft_get_forks(t_philo *d_philo);
void	ft_drop_forks(t_philo *d_philo);

#endif