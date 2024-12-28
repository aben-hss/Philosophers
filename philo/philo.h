/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:36:00 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 18:36:18 by aben-hss         ###   ########.fr       */
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

typedef enum s_mode
{
	ALLOC,
	FREE
}			t_mode;

typedef struct s_gc
{
	void			*content;
	struct s_gc		*next;
}					t_gc;

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
	pthread_mutex_t	*die;
	pthread_mutex_t	*meal_lock;
}			t_philo;

typedef struct s_data
{
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*die;
	pthread_mutex_t	*meal_lock;
	int				nbr_of_philos;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			nbr_of_meals;
	int				die_check;

}			t_data;

//gc
void		*ft_malloc(t_mode mode, int size);
// init
int			init_time(char **av, t_data *data);
int			init_resources(t_data *data);
int			init_philo(t_data *data);
t_philo		set_philo(t_data *data, int id);
// routine
void		ft_usleep(t_philo *philo, long time);
long		gettimestamp(void);
void		*simulation(void *ph);
// utils
long		cus_atol(char *str);
int			check_death(t_philo *philo);
void		print_it(t_philo *philo, char *str);
void		monitoring(t_data *data);
#endif
