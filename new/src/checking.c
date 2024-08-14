#include "../inc/header.h"

void	is_dead(t_philo *head)
{
	t_rules	*rul;

	rul = head->rul;
	pthread_mutex_lock(&(rul->print_mutex));
	if (get_time_ms(rul) - head->last_eat > rul->t2d)
	{
		rul->alive = DEAD;
	}
	pthread_mutex_unlock(&(rul->print_mutex));
}