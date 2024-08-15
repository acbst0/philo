#include "../inc/header.h"

t_philo	*add_philo(t_rules *rul, int i)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	new->number = i + 1;
	new->last_eat = 0;
	new->eat_times = 0;
	pthread_mutex_init(&(new->right), NULL);
	new->rul = rul;
	return (new);
}

t_philo	**init_philo(t_rules *rul)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = (t_philo **)malloc(sizeof(t_philo *) * rul->nop + 1);
	while (i < rul->nop)
	{
		philo[i] = add_philo(rul, i);
		if (i != 0)
			philo[i]->left = &(philo[i - 1]->right);
		if (i == (rul->nop - 1))
			philo[0]->left = &(philo[i]->right);
		i++;
	}
	philo[i] = NULL;
	rul->philos = philo;
	return (philo);
}
