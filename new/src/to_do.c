#include "../inc/header.h"

void	ft_sleep(t_philo *phi, unsigned long time)
{
	unsigned long	a_time;

	a_time = get_time_ms(phi->rul) + time;
	while (get_time_ms(phi->rul) < a_time)
		if (usleep(100) != 0)
			return ;
}

void	s_n_t(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_sleep(philo, philo->rul->t2s);
	print_status(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right));
	print_status(philo, "has taken a fork");
	if (philo->rul->nop == 1)
	{
		ft_sleep(philo, philo->rul->t2d * 2);
		return ;
	}
	pthread_mutex_lock(philo->left);
	print_status(philo, "has taken a fork");
	philo->eat_times++;
	philo->last_eat = get_time_ms(philo->rul);
	ft_sleep(philo, philo->rul->t2e);
	pthread_mutex_unlock(&(philo->right));
	pthread_mutex_unlock(philo->left);
}