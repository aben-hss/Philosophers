/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:27:45 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 19:41:54 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, long time)
{
	long	start;

	start = gettimestamp();
	while (gettimestamp() - start < time && !check_death(philo))
		usleep(100);
}

static void	*handle_eating(t_philo *philo)
{
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
	return ((void *)1);
}

static int	handle_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	print_it(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	print_it(philo, "has taken a fork");
	return (1);
}

static int	handle_post_meal(t_philo *philo)
{
	print_it(philo, "is sleeping");
	ft_usleep(philo, philo->t_to_sleep);
	if (check_death(philo))
		return (0);
	print_it(philo, "is thinking");
	return (1);
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
		if (!handle_forks(philo))
			return (NULL);
		if (!handle_eating(philo))
			return (NULL);
		if (!handle_post_meal(philo))
			return (NULL);
	}
}

// void	*simulation(void *ph)
// {
// 	t_philo	*philo;

// 	philo = ph;
// 	if (philo->id % 2 != 0)
// 	{
// 		ft_usleep(philo, 1);
// 		print_it(philo, "is thinking");
// 	}
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->r_fork);
// 		if (check_death(philo))
// 			return (pthread_mutex_unlock(philo->r_fork), NULL);
// 		print_it(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->l_fork);
// 		if (check_death(philo))
// 			return (pthread_mutex_unlock(philo->l_fork),
// 				pthread_mutex_unlock(philo->r_fork), NULL);
// 		print_it(philo, "has taken a fork");
// 		if (!handle_eating(philo))
// 			return (NULL);
// 		print_it(philo, "is sleeping");
// 		ft_usleep(philo, philo->t_to_sleep);
// 		if (check_death(philo))
// 			return (NULL);
// 		print_it(philo, "is thinking");
// 	}
// }

// void	*simulation(void *ph)
// {
// 	t_philo	*philo;

// 	philo = ph;
// 	if (philo->id % 2 != 0)
// 	{
// 		ft_usleep(philo, 1);
// 		print_it(philo, "is thinking");
// 	}
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->r_fork);
// 		if (check_death(philo))
// 			return (pthread_mutex_unlock(philo->r_fork), NULL);
// 		print_it(philo, "has taken a fork");
// 		if (philo->r_fork == philo->l_fork)
// 			return (NULL);
// 		pthread_mutex_lock(philo->l_fork);
// 		if (check_death(philo))
// 			return (pthread_mutex_unlock(philo->l_fork),
// 				pthread_mutex_unlock(philo->r_fork), NULL);
// 		print_it(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->meal_lock);
// 		if (!philo->nbr_of_meals--)
// 		{
// 			pthread_mutex_unlock(philo->l_fork);
// 			pthread_mutex_unlock(philo->r_fork);
// 			return (pthread_mutex_unlock(philo->meal_lock), NULL);
// 		}
// 		pthread_mutex_unlock(philo->meal_lock);
// 		print_it(philo, "is eating");
// 		pthread_mutex_lock(philo->die);
// 		philo->last_meal = gettimestamp();
// 		pthread_mutex_unlock(philo->die);
// 		ft_usleep(philo, philo->t_to_eat);
// 		if (check_death(philo))
// 			return (pthread_mutex_unlock(philo->r_fork),
// 				pthread_mutex_unlock(philo->l_fork), NULL);
// 		pthread_mutex_unlock(philo->r_fork);
// 		pthread_mutex_unlock(philo->l_fork);
// 		print_it(philo, "is sleeping");
// 		ft_usleep(philo, philo->t_to_sleep);
// 		if (check_death(philo))
// 			return (NULL);
// 		print_it(philo, "is thinking");
// 	}
// }
