#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FORK "has taken a fork"

# define DEAD 0
# define ALIVE 1

# define ERR_UNDF "Undefined Error!"
# define ERR_CTRD "Thread Creation Error!"
# define ERR_JTRD "Thread Joining Error!"

typedef struct rules
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				per_eat;
	long int		base_time;
	struct timeval	tv;
	pthread_mutex_t	print_mutex;
}	t_rules;

typedef struct philo_s
{
	pthread_t		thread;
	size_t			id;
	long int		last_eat;
	int				eat_times;
	pthread_mutex_t	*left;
	pthread_mutex_t	right;
	t_rules			*rul;
	struct philo_s	*next;
	struct philo_s	*prev;
}	t_philo;

//init
t_philo *init(char **av);

//UTILS
int	ft_atoi(const char *str);

//error and free
void	ft_error(char *str, t_philo *head);
void	free_all(t_philo *head);

//launch
void	launch(t_philo *head);

//time and status
long int get_time_long();
long int get_time(t_rules *rules);
void print_status(t_philo *philo, const char *status);

#endif