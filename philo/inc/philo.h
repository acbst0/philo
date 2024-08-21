/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:53:07 by abostano          #+#    #+#             */
/*   Updated: 2024/08/21 11:53:08 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define LEFT 0
# define RIGHT 1
# define LONG_MAX 9223372036854775807

typedef struct s_params
{
	int				num;
	int				ready;
	int				t2d;
	int				t2e;
	int				t2s;
	int				max_iter;
	int				check_meal;
	int				over;
	long int		start;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*fork;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		last_eat;
	pthread_t		life_tid;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	t_params		*par;
}	t_philo;

int			philosophers(t_params *p);
int			init_philo(t_params *p, t_philo *philo);
int			check_death(t_philo *p);
int			ft_atoi(const char *str);
int			ft_usleep(long int time);
int			error_msg(char *s, t_params *par, t_philo *p, int malloc);
void		*thread_routine(void *job);
void		final_print(int alive);
void		print_routine(t_philo *p, char *action);
long int	time_now(void);

#endif