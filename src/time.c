/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:30:04 by fboivin           #+#    #+#             */
/*   Updated: 2023/12/11 16:03:53 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

# define TEST_TIME 200
void    test_sleep_accuracy(void)
{
    struct timeval  start;
    struct timeval  end;
    long            seconds;
    long            microseconds;
    double          elapsed_milliseconds;
    gettimeofday(&start, NULL);
    //
    ft_usleep(TEST_TIME);
    //
    gettimeofday(&end, NULL);
    //
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed_milliseconds = (seconds * 1000) + (microseconds / 1000.0);
    //
    printf("Expected sleep duration:\t%d ms\n", TEST_TIME);
    printf("Actual sleep duration:\t\t%.2f ms\n", elapsed_milliseconds);
}

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
	usleep(milliseconds * (1000 - 100));
	while ((get_time() - start) < (milliseconds))
		usleep(50);
	return (0);
}
