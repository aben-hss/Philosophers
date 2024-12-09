/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:36:00 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/08 01:36:56 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>


typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			nbr_of_meals;
	long			start_time;
	long			last_meal;
	int				*die_check;
	pthread_mutex_t *die;
}			t_philo;

typedef struct s_data
{
	pthread_t 		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t *die;
	int				nbr_of_philos;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			nbr_of_meals;
	int				die_check;
}			t_data;

# endif
