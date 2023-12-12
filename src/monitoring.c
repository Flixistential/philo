/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:51:14 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/11 20:57:14 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int ft_deadcheck(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_flag);
	if (!*philo->dead_flag)
	{
		pthread_mutex_unlock(philo->mutex_flag);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex_flag);
		return (1);
	}
}


int	ft_checkmeal(t_philo *philo)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < philo[0].num_philo)
	{
		if (philo[i].num_meal == philo[i].meal_taken)
			j++;
		i++;
	}
	if (j == philo[0].num_philo)
	{
		printf("EVERYONE IS FULL\n");
		return(0);
	}
	else
		return(1);	
}

int	ft_deathwatch(t_philo *philo, t_deathwatch *dwatch)
{
	size_t	i;
	long 	time_to_die;

	i = 0;
	time_to_die = philo[0].time_to_die;
	while (!dwatch->dead_flag)
	{
		if(philo[0].num_meal > 0)
		{
			if (!ft_checkmeal(philo))
				return (0);
		}
		while (i < philo[0].num_philo)
		{
			pthread_mutex_lock(&philo[i].mutex_meal);
			if (get_time() > (philo[i].last_meal + time_to_die))
			{
				pthread_mutex_lock(&dwatch->mutex_flag);
				dwatch->dead_flag = 1;
				pthread_mutex_unlock(&dwatch->mutex_flag);
				pthread_mutex_lock(&dwatch->write);
				printf ("%ld %d %s\n", get_time(), (philo[i].index), DIE);
				pthread_mutex_unlock(&dwatch->write);
				pthread_mutex_unlock(&philo[i].mutex_meal);
				return (0);
			}
			pthread_mutex_unlock(&philo[i].mutex_meal);
			i++;
		}
		usleep(5000);
		i = 0;
	}
	return (0);
}
