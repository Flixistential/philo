/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:30:04 by fboivin           #+#    #+#             */
/*   Updated: 2023/11/08 12:09:04 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec * 0.001 - start.tv_usec * 0.001));
}

int	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	usleep(milliseconds * 1000 - 10);
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
