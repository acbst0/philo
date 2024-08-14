#include "../inc/header.h"

void	print_status(t_philo *philo, const char *txt)
{
	long int	time_in_ms;

	pthread_mutex_lock(&(philo->rul->print_mutex));
	time_in_ms = get_time_ms(philo->rul);
	printf("%ld ms : %zu %s\n", time_in_ms, philo->number, txt);
	pthread_mutex_unlock(&(philo->rul->print_mutex));
}