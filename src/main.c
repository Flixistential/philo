/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:11:49 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/11 17:42:31 by fboivin          ###   ########.fr       */
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

void	print_msg(t_philo *philo, char *msg)
{
	long	time;

	if (ft_deadcheck(philo))
		return;
	time = (get_time() - philo->start_time);
	if (get_time() > (philo->last_meal + philo->time_to_die))
	{
		pthread_mutex_lock(philo->mutex_flag);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo->mutex_flag);
		pthread_mutex_lock(philo->write);
		printf ("%ld %d %s\n", get_time(), (philo->index), DIE);
		pthread_mutex_unlock(philo->write);
	}
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

void	*ft_test(void *p)
{
	t_philo	*philo;
	long start_time;

	start_time = get_time();
	philo = (t_philo *)p;
	philo->start_time = start_time;
	philo->last_meal = start_time;
	if (philo->index %2 != 0)
		ft_usleep(philo->time_to_eat * 0.5);
	if (!philo->num_meal)
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
	else if (philo->num_meal > 0)
	{
		while (!ft_deadcheck(philo) && philo->meal_taken < philo->num_meal)
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
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	fork[MAX_PHILO];
	size_t			i;
	t_deathwatch	dwatch;

	i = 0;
	//test_sleep_accuracy();
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
	//ft_deathwatch(philo, &dwatch);
	i = 0;
	//make a join and destroy mutex
	while (i < philo[0].num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
