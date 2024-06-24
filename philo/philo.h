/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:36 by abostano          #+#    #+#             */
/*   Updated: 2024/05/28 13:49:28 by abostano         ###   ########.fr       */
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
# define ERR_THRD "Thread error!\n"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct rules
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	per_eat;
}	t_rules;

typedef struct forks_s
{
	int				fork_number;
	int				status;
	pthread_mutex_t mutex;
	struct forks_s	*next;
	struct forks_s	*prev;
}	t_forks;

typedef struct philo_s
{
	pthread_t		thread;
	size_t			number;
	int				last_eat;
	int				last_thinking;
	int				last_sleep;
	int				eat_times;
	t_forks			*left;
	t_forks			*right;
	struct philo_s	*next;
	struct philo_s	*prev;
	t_rules			*rul;
}	t_philo;

//utils
int		ft_atoi(const char *str);
void	ft_error(char *str);
void	free_philo_fork(t_philo *head);
//init
void	add_details(t_philo *new, t_forks *new_fork);
void	add_philo(t_philo **head);
void	set_rules(char **av, t_rules *rul);
void	make_circle(t_philo **head, t_rules *rul);
t_philo	*init_philo(char **av, t_rules *rul);

void working(t_philo *head);
#endif