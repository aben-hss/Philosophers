/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:43:56 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 17:59:44 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			simulation, &data.philos[i]); // protect
		i++;
	}
	monitoring(&data);
	i = 0;
	while (i < data.nbr_of_philos)
		pthread_join(data.threads[i++], NULL); // protect
	return (1);
}
