/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:24:06 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/29 10:44:22 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->die);
	if (*philo->die_check)
	{
		pthread_mutex_unlock(philo->die);
		return (1);
	}
	pthread_mutex_unlock(philo->die);
	return (0);
}

void	print_it(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->die);
	printf("%ld %d %s\n", gettimestamp() - philo->start_time, \
		philo->id, str);
	pthread_mutex_unlock(philo->die);
}

static int	check_meals_status(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (!philo->nbr_of_meals)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	check_death_status(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(data->die);
	if (gettimestamp() - philo->last_meal > data->t_to_die)
	{
		data->die_check = 1;
		pthread_mutex_unlock(data->die);
		usleep(2000);
		print_it(philo, "died");
		return (1);
	}
	pthread_mutex_unlock(data->die);
	return (0);
}

void	monitoring(t_data *data)
{
	int		i;
	t_philo	*philo;

	while (1 && data->nbr_of_philos)
	{
		i = 0;
		while (i < data->nbr_of_philos)
		{
			philo = &data->philos[i];
			if (check_meals_status(philo))
				return ;
			if (check_death_status(data, philo))
				return ;
			i++;
		}
	}
}
