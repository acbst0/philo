#include "../inc/philo.h"

long int get_time_long()
{
	long int	tmp;
	struct timeval tv;

    gettimeofday(&tv, NULL);
	tmp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (tmp);
}

long int get_time(t_rules *rules)
{
	long int	tmp;
	struct timeval	tv;

    gettimeofday(&tv, NULL);
	tmp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	tmp = tmp - rules->base_time;
	return (tmp);
}

void print_status(t_philo *philo, const char *status)
{
	long int time_in_ms;

	// Pointerların geçerli olup olmadığını kontrol edelim
	if (philo == NULL || !philo->rul)
		ft_error(ERR_UNDF, philo);
	time_in_ms = get_time(philo->rul);
	if (status == EAT)
	{
		philo->last_eat = time_in_ms;
		philo->eat_times += 1;
	}
	printf("%ld ms : %zu %s\n", time_in_ms, philo->id, status);
}
