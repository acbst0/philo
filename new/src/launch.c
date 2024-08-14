#include "../inc/header.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_rules	*rul;

	philo = (t_philo *)ptr;
	rul = philo->rul;
	while (rul->alive)
	{
		is_dead(philo);
		eat(philo);
		s_n_t(philo);
	}
}

int	launch(t_philo **head)
{
	t_rules	*rul;
	int		i;

	i = 0;
	rul = head[0]->rul;
	rul->base_time = get_time_pure();
	while (i < rul->nop)
	{
		if (pthread_create(&(head[i]->thread), NULL,
						routine, (void *)head[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < rul->nop)
	{
		if (pthread_join(head[i]->thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}