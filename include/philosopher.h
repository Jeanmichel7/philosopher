/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:25:22 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/06 16:22:38 by jrasser          ###   ########.fr       */
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

typedef struct t_philo
{
	char			*state;
	pthread_t		id_thread;
	unsigned int	id;
	int				isAlive;
	t_time			time;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;

}	t_philo;



typedef struct s_data
{
	unsigned int	nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	*tab_time_each_eat;
	int				isAllAlive;
	t_time			time;
	t_philo			*tab_philos;
}	t_data;




int			ft_check_arg(int argc, char **argv);
t_data		ft_get_args(char **argv);


/*  TIME  */
long	time_diff(struct timeval *start, struct timeval *end);
void	ft_print_time_diff(t_data *data, char *str);
void	ft_print_time_diff_philo(t_philo *data, char *str);

#endif