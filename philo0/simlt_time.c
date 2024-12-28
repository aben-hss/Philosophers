/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simlt_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:27:45 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 17:53:41 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettimestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(t_philo *philo, long time)
{
	long	start;

	start = gettimestamp();
	while (gettimestamp() - start < time && !check_death(philo))
		usleep(100);
}

void	*simulation(void *ph)
{
	t_philo	*philo;

	philo = ph;
	if (philo->id % 2 != 0)
	{
		ft_usleep(philo, 1);
		print_it(philo, "is thinking");
	}
	while (1)
	{
		pthread_mutex_lock(philo->r_fork);
		if (check_death(philo))
			return (pthread_mutex_unlock(philo->r_fork), NULL);
		print_it(philo, "has taken a fork");
		if (philo->r_fork == philo->l_fork)
			return (NULL);
		pthread_mutex_lock(philo->l_fork);
		if (check_death(philo))
			return (pthread_mutex_unlock(philo->l_fork),
				pthread_mutex_unlock(philo->r_fork), NULL);
		print_it(philo, "has taken a fork");
		pthread_mutex_lock(philo->meal_lock);
		if (!philo->nbr_of_meals--)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (pthread_mutex_unlock(philo->meal_lock), NULL);
		}
		pthread_mutex_unlock(philo->meal_lock);
		print_it(philo, "is eating");
		pthread_mutex_lock(philo->die);
		philo->last_meal = gettimestamp();
		pthread_mutex_unlock(philo->die);
		ft_usleep(philo, philo->t_to_eat);
		if (check_death(philo))
			return (pthread_mutex_unlock(philo->r_fork),
				pthread_mutex_unlock(philo->l_fork), NULL);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_it(philo, "is sleeping");
		ft_usleep(philo, philo->t_to_sleep);
		if (check_death(philo))
			return (NULL);
		print_it(philo, "is thinking");
	}
}
