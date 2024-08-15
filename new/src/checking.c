#include "../inc/header.h"

int	is_dead(t_philo *philo)
{
	t_rules		*rul;
	long int	current_time;
	long int	time_since_last_meal;

	rul = philo->rul;
	current_time = get_time_ms(rul);
	time_since_last_meal = current_time - philo->last_eat;
	if (time_since_last_meal > rul->t2d)
	{
		rul->alive = DEAD;
		return (DEAD);
	}
	return (ALIVE);
}

int check_all_philos_ate(t_philo **philos)
{
    int i;
    t_rules *rul;

    rul = philos[0]->rul;
    if (rul->et == -1)
        return (ALIVE);
    i = 0;
    while (i < rul->nop)
    {
        if (philos[i]->eat_times < rul->et)
            return (ALIVE);
        i++;
    }
    return (ALLEAT);
}
