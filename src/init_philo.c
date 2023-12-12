/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:26:47 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/12 18:22:08 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_initshared(t_philo *philo, t_deathwatch *dwatch)
{
	size_t	i;

	i = 0;
	while (i < philo[0].num_philo)
	{
		philo[i].dead_flag = &dwatch->dead_flag;
		philo[i].write = &dwatch->write;
		philo[i].mutex_flag = &dwatch->mutex_flag;
		i++;
	}
}

void	init_dw(t_deathwatch *dwatch)
{
	dwatch->dead_flag = 0;
	pthread_mutex_init(&dwatch->write, NULL);
	pthread_mutex_init(&dwatch->mutex_flag, NULL);
}

void	ft_initdata(size_t p_num, t_philo *philo, char **arg)
{
	size_t	i;

	i = 0;
	while (i < p_num)
	{
		philo[i].index = (i + 1);
		philo[i].time_to_die = ft_atoui(arg[2]);
		philo[i].time_to_eat = ft_atoui(arg[3]);
		philo[i].time_to_sleep = ft_atoui(arg[4]);
		philo[i].num_philo = p_num;
		if (arg[5])
			philo[i].num_meal = ft_atoui(arg[5]);
		else
			philo[i].num_meal = 0;
		philo[i].meal_taken = 0;
		i++;
	}
}

int	ft_makephilo(char **arg, t_philo *philo, t_deathwatch *dwatch)
{
	size_t			p_num;

	p_num = ft_atoui(arg[1]);
	if (p_num == 0)
		return (ft_error(2));
	init_dw(dwatch);
	ft_initdata(p_num, philo, arg);
	ft_initshared(philo, dwatch);
	return (0);
}

void	ft_makefork(t_philo *philo, pthread_mutex_t *fork)
{
	size_t	i;

	i = 0;
	while (i < philo[0].num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_mutex_init(&philo[i].mutex_meal, NULL);
		i++;
	}
	i = 0;
	while (i < ((philo[0].num_philo) - 1))
	{
		philo[i].l_fork = &fork[i];
		philo[i].r_fork = &fork[i + 1];
		i++;
	}
	philo[i].l_fork = &fork[i];
	philo[i].r_fork = &fork[0];
}
