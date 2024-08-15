#include "../inc/header.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_rules	*rul;

	philo = (t_philo *)ptr;
	rul = philo->rul;
	while (rul->alive == ALIVE)
	{
		eat(philo);
		if (rul->alive == ALIVE)
		{
			s_n_t(philo);
		}
	}
	return (NULL);
}

void	die_routine(t_philo **head, t_rules *rul)
{
	int	i;

	i = 0;
	while (rul->alive)
	{
		usleep(100);
		i = 0;
		while (head[i])
		{
			if (is_dead(head[i]) == DEAD)
			{
				print_status(head[i], "died");
				rul->alive = DEAD;
				break ;
			}
			i++;
		}
	}
	if (check_all_philos_ate(head) == ALLEAT)
		rul->alive = ALLEAT;
}

int	launch(t_philo **head)
{
	t_rules	*rul;
	int		i;

	i = 0;
	rul = head[0]->rul;
	rul->base_time = get_time_pure();
	while (head[i])
	{
		pthread_create(&(head[i]->thread), NULL, routine, head[i]);
		i++;
	}
	die_routine(head, rul);
	i = 0;
	while (head[i])
	{
		pthread_join(head[i]->thread, NULL);
		i++;
	}
	return (1);
}
