/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:51:14 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/12 18:31:35 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_deadcheck(t_philo *philo)
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
	size_t	i;
	size_t	j;

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
		return (0);
	}
	else
		return (1);
}

void	ft_max_meal(t_philo *philo)
{
	while (!ft_deadcheck(philo) && philo->meal_taken < philo->num_meal)
	{
		pthread_mutex_lock (philo->r_fork);
		print_msg (philo, FORK);
		pthread_mutex_lock (philo->l_fork);
		print_msg(philo, FORK);
		print_msg(philo, EAT);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		if (philo->meal_taken < philo->num_meal)
		{
			print_msg(philo, SLEEP);
			ft_usleep(philo->time_to_sleep);
			print_msg(philo, THINK);
		}
	}
}

void	ft_infinite(t_philo *philo)
{
	while (!ft_deadcheck(philo))
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, FORK);
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, FORK);
		print_msg(philo, EAT);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_msg(philo, SLEEP);
		ft_usleep(philo->time_to_sleep);
		print_msg(philo, THINK);
	}
}
