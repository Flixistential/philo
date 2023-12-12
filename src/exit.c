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

int ft_joinanddestroy(t_philo *philo,t_deathwatch *dwatch)
{
    size_t i;

    i = 0;
	while (i < philo[0].num_philo)
	{
		if(pthread_join(philo[i].thread, NULL))
			ft_error(5);
		i++;
	}
    i = 0;
    while (i < philo[0].num_philo)
    {
        if(pthread_mutex_destroy(philo[i].l_fork) ||\
            pthread_mutex_destroy(&philo[i].mutex_meal))
            ft_error(6);
        i++;
    }
    if(pthread_mutex_destroy(dwatch->mutex_meal))
         ft_error(6);
    if(pthread_mutex_destroy(&dwatch->write))
         ft_error(6);
    return(0);
}