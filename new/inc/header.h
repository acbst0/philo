#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define DEAD 0
# define ALIVE 1

typedef struct rules
{
	int				nop;
	int				t2d;
	int				t2e;
	int				t2s;
	int				et;
	long int		base_time;
	pthread_mutex_t	print_mutex;
	struct timeval	tv;
}	t_rules;

typedef struct philo_s
{
	pthread_t		thread;
	size_t			number;
	long int		last_eat;
	int				eat_times;
	int				alive;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_rules			*rul;
}	t_philo;

//utils
int	ft_atoi(const char *str);
#endif