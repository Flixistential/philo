/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:11:49 by fboivin           #+#    #+#             */
/*   Updated: 2023/11/08 12:08:48 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(philo->write);
	time = (get_time() - philo->start_time);
	if (ft_strncmp(msg, "is eating", 9) == 0)
	{
		pthread_mutex_lock(&philo->mutex_meal);
		philo->last_meal = time;
		philo->meal_taken++;
		pthread_mutex_unlock(&philo->mutex_meal);
	}
	pthread_mutex_lock(philo->mutex_flag);
	if (!*philo->dead_flag)
		printf ("%ld %d %s\n", time, (philo->index), msg);
	pthread_mutex_unlock(philo->mutex_flag);
	pthread_mutex_unlock(philo->write);
}

void	*ft_test(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->index %2 != 0)
		usleep(philo->time_to_eat * 1000 * 0.5);
	if (!philo->num_meal)
	{
		while (!*philo->dead_flag)
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
	else if (philo->num_meal > 0)
	{
		while (!*philo->dead_flag && philo->meal_taken < philo->num_meal)
		{
			pthread_mutex_lock(philo->r_fork);
			print_msg(philo, FORK);
			pthread_mutex_lock(philo->l_fork);
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
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			philo[200];
	pthread_mutex_t	fork[200];
	size_t			i;
	t_deathwatch	dwatch;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (ft_numcheck(argv) != 0)
		return (-1);
	if (ft_atoui(argv[1]) == 1)
		return(ft_onephilo(argv));
	if (ft_makephilo (argv,  philo, &dwatch) < 0)
		return (-1);
	ft_makefork(philo, fork);
	while (i < philo[0].num_philo)
	{
		if (pthread_create(&philo[i].thread, \
			NULL, ft_test, (void *)&philo[i]) != 0)
			return (ft_error(4));
		i++;
	}
	ft_deathwatch(philo, &dwatch);
	i = 0;
	//make a join and destroy mutex
	while (i < philo[0].num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
