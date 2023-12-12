/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:19:05 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/12 00:19:05 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_joinanddestroy(t_philo *philo, t_deathwatch *dwatch)
{
	size_t	i;

	i = 0;
	while (i < philo[0].num_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			ft_error(5);
		i++;
	}
	i = 0;
	while (i < philo[0].num_philo)
	{
		if (pthread_mutex_destroy(philo[i].l_fork) || \
			pthread_mutex_destroy(&philo[i].mutex_meal))
			ft_error(6);
		i++;
	}
	if (dwatch)
		return (0);
	if (pthread_mutex_destroy(&dwatch->write))
		ft_error (6);
	return (0);
}

void	ft_death(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_flag);
	if (*philo->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->mutex_flag);
		return ;
	}
	*philo->dead_flag = 1;
	pthread_mutex_unlock(philo->mutex_flag);
	pthread_mutex_lock(philo->write);
	printf ("%ld %d %s\n", get_time(), (philo->index), DIE);
	pthread_mutex_unlock(philo->write);
}
