/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:43:56 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 19:46:54 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettimestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (1);
	if (!init_time(av, &data))
		return (2);
	if (!init_philo(&data))
		return (3);
	while (i < data.nbr_of_philos)
	{
		data.philos[i].start_time = gettimestamp();
		data.philos[i].last_meal = gettimestamp();
		pthread_create(&data.threads[i], NULL,
			simulation, &data.philos[i]);
		i++;
	}
	monitoring(&data);
	i = 0;
	while (i < data.nbr_of_philos)
		pthread_join(data.threads[i++], NULL);
	return (1);
}
