/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:36 by abostano          #+#    #+#             */
/*   Updated: 2024/07/24 18:33:36 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define ERR_NOF "Philo needs 4 or 5 int\n"
# define ERR_THRD "Thread joining error!\n"
# define ERR_THRD_CR "Thread creating error!\n"
# define PTR_ERR "ERROR\n"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "dead"
# define DIE 0
# define ALIVE 1

typedef struct rules
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				per_eat;
	long int		base_time;
	pthread_mutex_t	print_mutex;
	struct timeval	tv;
}	t_rules;

typedef struct forks_s
{
	int				fork_number;
	int				status;
	pthread_mutex_t	mutex;
	struct forks_s	*next;
	struct forks_s	*prev;
}	t_forks;

typedef struct philo_s
{
	pthread_t		thread;
	size_t			number;
	long int		last_eat;
	int				eat_times;
	int				alive;
	t_forks			*left;
	t_forks			*right;
	struct philo_s	*next;
	struct philo_s	*prev;
	t_rules			*rul;
}	t_philo;

int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_error(char *str, t_philo *head);
void		free_philo_fork(t_philo *head);

void		add_details(t_philo *new, t_forks *new_fork);
void		add_philo(t_philo **head);
void		set_rules(char **av, t_rules *rul);
void		make_circle(t_philo **head, t_rules *rul);
t_philo		*init_philo(char **av, t_rules *rul);

long int	get_time(t_rules *rules);
void		print_status(t_philo *philo, const char *status);

void		checkdie(t_philo *philo);
void		checkeattimes(t_philo *head);

void		ft_sleep(t_philo *phi, unsigned long time);
void		launch(t_philo *head);

void		ssleep(t_philo *philo);
void		think(t_philo *philo);
void		eat(t_philo *head);
#endif