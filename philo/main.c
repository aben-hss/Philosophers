/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:48:51 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 03:12:19 by aben-hss         ###   ########.fr       */
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
			data -> nbr_of_meals == -1)
		return (0);
	return (1);
}
long gettimestamp()
{
	struct timeval tv;

	gettimeofday(&tv,NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
t_philo set_philo(t_data *data, int id)
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
	if(id == data->nbr_of_philos)
		new.l_fork = &data->forks[0];
	else
		new.l_fork = &data->forks[id];
	return (new);
}
int init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data ->nbr_of_philos);
	if (!data->forks)
		return (free(data->philos),0);
	i = 0;
	while(i < data->nbr_of_philos)
		pthread_mutex_init(&data->forks[i++],NULL);
	i = 0;
	data->die_check = 0;
	data->die = malloc(sizeof(pthread_mutex_t));
	if(!data->die)
		return (free(data->philos),free(data->forks),0);
	pthread_mutex_init(data->die,NULL); // p rotect it
	data->threads = malloc(sizeof(pthread_t) * data->nbr_of_philos); // protect it  protect it free the previes
	data->meal_lock = malloc(sizeof(pthread_mutex_t)); // protect it  protect it free the previes
	pthread_mutex_init(data->meal_lock,NULL); // p rotect it
	while(i < data->nbr_of_philos)
	{
		data->philos[i] = set_philo(data,i+1);
		i++;
	}
	return(1);
}
int check_death(t_philo  *philo)
{
	pthread_mutex_lock(philo->die);
	if(*philo->die_check)
	{
		pthread_mutex_unlock(philo->die);
		return(1);
	}
	pthread_mutex_unlock(philo->die);
	return(0);
}
void ft_usleep(t_philo *philo,long time)
{
	long start = gettimestamp();
	while(gettimestamp() - start < time && !check_death(philo))
		usleep(100);
}

void print_it (t_philo *philo,char *str)
{
	pthread_mutex_lock(philo->die);
	printf("%ld %d %s\n",gettimestamp()-philo->start_time,philo->id,str);
	pthread_mutex_unlock(philo->die);
}
void *simulation(void *ph)
{
	t_philo *philo = ph;

	if(philo->id % 2 != 0)
	{
	 	ft_usleep(philo,1);
		print_it(philo,"is thinking");
	}
	while(1)
	{
		pthread_mutex_lock(philo->r_fork);
		if(check_death(philo))
			return(pthread_mutex_unlock(philo->r_fork),NULL);
		print_it(philo,"has taken a fork");
		if (philo->r_fork == philo->l_fork)
			return (NULL);
		pthread_mutex_lock(philo->l_fork);
		if(check_death(philo))
			return(pthread_mutex_unlock(philo->l_fork), pthread_mutex_unlock(philo->r_fork),NULL);
		print_it(philo,"has taken a fork");
		pthread_mutex_lock(philo->meal_lock);
		if(!philo->nbr_of_meals--)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (pthread_mutex_unlock(philo->meal_lock), NULL);
		}
		pthread_mutex_unlock(philo->meal_lock);
		print_it(philo,"is eating");
		pthread_mutex_lock(philo->die);
		philo->last_meal = gettimestamp();
		pthread_mutex_unlock(philo->die);
		ft_usleep(philo,philo->t_to_eat);
		if(check_death(philo))
			return(pthread_mutex_unlock(philo->r_fork),pthread_mutex_unlock(philo->l_fork),NULL);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_it(philo,"is sleeping");
		ft_usleep(philo,philo->t_to_sleep);
		if(check_death(philo))
			return(NULL);
		print_it(philo,"is thinking");
	}
}
void l9wad(t_data *data)
{
	int i;

	t_philo *philo;
	while(1)
	{
		i = 0;
		while(i < data->nbr_of_philos)
		{
			philo = &data->philos[i];
			pthread_mutex_lock(philo->meal_lock);
			if(!philo->nbr_of_meals)
			{
				pthread_mutex_unlock(philo->meal_lock);
				return ;
			}
			pthread_mutex_unlock(philo->meal_lock);
			pthread_mutex_lock(data->die);
			if(gettimestamp() - philo->last_meal > data->t_to_die)
			{
				data->die_check = 1;
				pthread_mutex_unlock(data->die);
				print_it(philo,"died");
				return ;
			}
			pthread_mutex_unlock(data->die);
			i++;
		}
	}
}
int main(int ac, char **av)
{
	t_data	data;
	int i = 0;
	if (ac != 5 && ac != 6)
		return (1);
	if (!init_time(av, &data))
		return (2);
	if (!init_philo(&data))
		return(3);

	while (i < data.nbr_of_philos)
	{
		data.philos[i].start_time = gettimestamp();
		data.philos[i].last_meal = gettimestamp();
		pthread_create(&data.threads[i],NULL,simulation,&data.philos[i]); // protect
		i++;
	}
	l9wad(&data);
	i = 0;
	while(i < data.nbr_of_philos)
		pthread_join(data.threads[i++],NULL); // protect
	return(1);
}
