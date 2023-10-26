/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:01:03 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/25 17:10:21 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>

void		ft_putchar_fd(char c, int fd);
size_t		ft_atoui(const char *str);
void		ft_putendl_fd(char *s, int fd);
int			ft_strlen(char *str);
int			ft_error(int err);
int			ft_strlen(char *str);

typedef struct s_philo
{
	pthread_t	thread;
	int			index;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		num_philo;
	size_t		num_meal;
}		t_philo;

#endif