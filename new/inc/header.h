#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define DEAD 0
# define ALIVE 1
# define ALLEAT 2
# define ONLY 3

typedef struct rules
{
	int				nop;
	long int		t2d;
	int				t2e;
	int				t2s;
	int				et;
	long int		base_time;
	int				alive;
	pthread_mutex_t	print_mutex;
	struct philo_s	**philos;
}	t_rules;

typedef struct philo_s
{
	pthread_t		thread;
	size_t			number;
	long int		last_eat;
	int				eat_times;
	pthread_mutex_t	*left;
	pthread_mutex_t	right;
	t_rules			*rul;
}	t_philo;

//launch.c
int	launch(t_philo **head);
//utils
int	ft_atoi(const char *str);
int	ft_strcmp(const char *str1, const char *str2);
//init_philo.c
t_philo	**init_philo(t_rules *rul);
//init_rule.c
t_rules	*init_rule(int ac, char **av);
//get_time.c
long int	get_time_pure();
long int	get_time_ms(t_rules *rules);
//printing.c
void	print_status(t_philo *philo, const char *txt);
//checking.c
int	is_dead(t_philo *head);
int	check_all_philos_ate(t_philo **philos);
//to_do.c
void	ft_sleep(t_philo *phi, unsigned long time);
void	s_n_t(t_philo *philo);
void	eat(t_philo *philo);
#endif