/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:11:49 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/26 01:09:50 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	ft_error(int err)
{
	if (err == 0)
		ft_putendl_fd("Argument must be positive numbers", 2);
	else if (err == 1)
		ft_putendl_fd("wrong number of argument", 2);
	else if (err == 2)
		ft_putendl_fd("must have at least 1 philosopher", 2);
	else if (err == 3)
		ft_putendl_fd("Input too long", 2);
	else if (err == 4)
		ft_putendl_fd("Error while creating thread", 2);
	return (-1);
}

int	ft_numcheck(char **arg)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arg[i])
	{
		if (ft_strlen(arg[i]) > 10)
			return (ft_error(3));
		while (arg[i][j])
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (ft_error(0));
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int 	ft_makephilo(char **arg, t_philo *philo)
{
	size_t	p_num;
	size_t	i;

	i = 0;
	p_num = ft_atoui(arg[1]);
	if (p_num == 0)
		return (ft_error(2));
	//philo = (t_philo *)malloc(p_num * sizeof(t_philo));
	while (i < p_num)
	{
		philo[i].index = i;
		philo[i].time_to_die = ft_atoui(arg[2]);
		philo[i].time_to_eat = ft_atoui(arg[3]);
		philo[i].time_to_sleep = ft_atoui(arg[4]);
		philo[i].num_philo = p_num;
		if (arg[5])
			philo[i].num_meal = ft_atoui(arg[5]);	
		i++;
	}
	return (0);
}

void 	*ft_test(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	printf("philo index = %d\n", philo->index);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	philo[200];
	size_t 	i;

	i = 0;
	//philo = NULL;
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (ft_numcheck(argv) != 0)
		return (-1);
	if (ft_makephilo(argv,  philo) < 0)
		return (-1);
	while (i < philo[0].num_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_test,(void *)&philo[i]) != 0)
			return (ft_error(4));
		i++;
	}
	i = 0;
	while(i < philo[0].num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
