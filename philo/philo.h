#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct rules
{
	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;
	int	per_eat;
}	rules;

typedef struct forks_s
{
	int	fork_number;
	int	status;
	struct fork_s	*next;
	struct fork_s	*prev;
}	forks_t;

typedef struct philo_s
{
	size_t			number;
	int 			last_eat;
	int				last_thinking;
	int 			last_sleep;
	forks_t			*left;
	forks_t			*right;
	struct philo_s	*next;
	struct philo_s 	*prev;
}	philo_t;

//utils
int	ft_atoi(const char *str);
//init
void	add_details(philo_t *new, forks_t *new_fork);
void	add_philo(philo_t **head, char *av[]);
void	set_rules(char **av, rules *rul);
void	make_circle(philo_t **head);
philo_t	*init_philo(char **av, rules *rul);

#endif