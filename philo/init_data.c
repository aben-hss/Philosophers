/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:11 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/29 02:17:02 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(char **av, t_data *data)
{
	data -> nbr_of_philos = cus_atol(av[1]);
	data -> t_to_die = cus_atol(av[2]);
	data -> t_to_eat = cus_atol(av[3]);
	data -> t_to_sleep = cus_atol(av[4]);
	if (av[5])
		data ->nbr_of_meals = cus_atol(av[5]);
	else
		data -> nbr_of_meals = -2;
	if (data->nbr_of_philos == -1 || data ->t_to_die == -1 || \
			data ->t_to_eat == -1 || data ->t_to_sleep == -1 || \
			data -> nbr_of_meals == -1 || data->nbr_of_philos == 0 \
			|| data->nbr_of_meals == 0)
		return (0);
	return (1);
}

int	init_resources(t_data *data)
{
	int	i;

	i = -1;
	data->philos = ft_malloc(ALLOC, sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		return (0);
	data->forks = ft_malloc(ALLOC, sizeof(pthread_mutex_t) * \
		data->nbr_of_philos);
	if (!data->forks)
		return (0);
	while (++i < data->nbr_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	data->die = ft_malloc(ALLOC, sizeof(pthread_mutex_t));
	if (!data->die)
		return (0);
	pthread_mutex_init(data->die, NULL);
	data->threads = ft_malloc(ALLOC, sizeof(pthread_t) * data->nbr_of_philos);
	if (!data->threads)
		return (0);
	data->meal_lock = ft_malloc(ALLOC, sizeof(pthread_mutex_t));
	if (!data->meal_lock)
		return (0);
	pthread_mutex_init(data->meal_lock, NULL);
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	if (!init_resources(data))
		return (0);
	while (++i < data->nbr_of_philos)
		data->philos[i] = set_philo(data, i + 1);
	return (1);
}

t_philo	set_philo(t_data *data, int id)
{
	t_philo	new;

	new.id = id;
	new.t_to_die = data->t_to_die;
	new.t_to_eat = data->t_to_eat;
	new.t_to_sleep = data ->t_to_sleep;
	new.nbr_of_meals = data ->nbr_of_meals;
	new.die_check = &data->die_check;
	new.die = data->die;
	new.r_fork = &data->forks[id -1];
	new.meal_lock = data->meal_lock;
	if (id == data->nbr_of_philos)
		new.l_fork = &data->forks[0];
	else
		new.l_fork = &data->forks[id];
	return (new);
}
