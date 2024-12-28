/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:24:06 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 17:58:06 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	cus_atol(char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *(str++) - '0';
		if (res > INT_MAX)
			return (-1);
	}
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str)
		return (-1);
	return (res);
}

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
	printf("%ld %d %s\n", gettimestamp()-philo->start_time,
		philo->id, str);
	pthread_mutex_unlock(philo->die);
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
			pthread_mutex_lock(philo->meal_lock);
			if (!philo->nbr_of_meals)
				retrun(pthread_mutex_unlock(philo->meal_lock), NULL);
			pthread_mutex_unlock(philo->meal_lock);
			pthread_mutex_lock(data->die);
			if (gettimestamp() - philo->last_meal > data->t_to_die)
			{
				data->die_check = 1;
				pthread_mutex_unlock(data->die);
				return (print_it(philo, "died"), NULL);
			}
			pthread_mutex_unlock(data->die);
			i++;
		}
	}
}
