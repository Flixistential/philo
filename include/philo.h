/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:01:03 by fboivin           #+#    #+#             */
/*   Updated: 2023/11/03 18:02:58 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define EAT "is eating \U0001F35D"
# define SLEEP "is sleeping \U0001F6CF"
# define THINK "is thinking"
# define FORK "has taken a fork \U0001F374"
# define DIE "died ☠️"

/*
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking"
# define FORK "has taken a fork\n"
# define DIE "died\n"
*/

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	size_t			num_philo;
	size_t			num_meal;
	size_t			meal_taken;
	int				*dead_flag;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	*mutex_flag;
}		t_philo;

typedef struct s_deathwatch
{
	int				dead_flag;
	pthread_mutex_t	write;
	pthread_mutex_t	*mutex_meal;
	pthread_mutex_t	mutex_flag;
}		t_deathwatch;

void	ft_putchar_fd(char c, int fd);
size_t	ft_atoui(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(char *str);
int		ft_error(int err);
int		ft_strlen(char *str);
long	get_time(void);
int		ft_usleep(long milliseconds);
void	ft_initdata(size_t p_num, t_philo *philo, char **arg);
int		ft_makephilo(char **arg, t_philo *philo, t_deathwatch *d_watch);
int		ft_numcheck(char **arg);
void	ft_makefork(t_philo *philo, pthread_mutex_t *fork);
void	print_msg(t_philo *philo, char *msg);
void	init_dw(t_deathwatch *dwatch);
void	ft_initshared(t_philo *philo, t_deathwatch *dwatch);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_deathwatch(t_philo *philo, t_deathwatch *dwatch);
int		ft_checkmeal(t_philo *philo);
int		ft_onephilo(char **argv);

#endif
