/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:11:49 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/12 18:30:42 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	long	time;

	if (ft_deadcheck(philo))
		return ;
	time = (get_time() - philo->start_time);
	if (get_time() > (philo->last_meal + philo->time_to_die))
		(ft_death(philo));
	if (ft_strncmp(msg, "is eating", 9) == 0)
	{
		pthread_mutex_lock(&philo->mutex_meal);
		philo->last_meal = time;
		philo->meal_taken++;
		pthread_mutex_unlock(&philo->mutex_meal);
	}
	pthread_mutex_lock(philo->mutex_flag);
	if (!*philo->dead_flag)
	{
		pthread_mutex_lock(philo->write);
		printf ("%ld %d %s\n", time, (philo->index), msg);
		pthread_mutex_unlock(philo->write);
	}
	pthread_mutex_unlock(philo->mutex_flag);
}

void	*ft_routine(void *p)
{
	t_philo	*philo;
	long	start_time;

	start_time = get_time();
	philo = (t_philo *)p;
	philo->start_time = start_time;
	philo->last_meal = start_time;
	if (philo->index % 2 != 0)
		ft_usleep(philo->time_to_eat * 0.5);
	if (!philo->num_meal)
		ft_infinite(philo);
	else if (philo->num_meal > 0)
		ft_max_meal(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	fork[MAX_PHILO];
	size_t			i;
	t_deathwatch	dwatch;

	i = 0;
	if (ft_parse(argc, argv) == -1)
		return (-1);
	if (ft_makephilo (argv, philo, &dwatch) < 0)
		return (-1);
	ft_makefork(philo, fork);
	while (i < philo[0].num_philo)
	{
		if (pthread_create(&philo[i].thread, \
			NULL, ft_routine, (void *)&philo[i]) != 0)
			return (ft_error(4));
		i++;
	}
	ft_joinanddestroy(philo, &dwatch);
}
