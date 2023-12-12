/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:35:42 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/12 00:16:29 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_onephilo(char **argv)
{
	printf("0 1 has taken a fork\n");
	usleep((ft_atoui(argv[2]) * 1000));
	printf("%s 1 died\n",argv[2]);
	return(0);
}

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
	else if(err == 5)
		ft_putendl_fd("Error while joining thread", 2);
	else if(err == 6)
		ft_putendl_fd("Error while destroying thread", 2);
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

int ft_parse(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (ft_numcheck(argv) != 0)
		return (-1);
	if (ft_atoui(argv[1]) == 1)
		return(ft_onephilo(argv));
	return (0);
}