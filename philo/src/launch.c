#include "../philo.h"

void	ft_sleep(t_philo *phi, unsigned long time)
{
	unsigned long	a_time;

	a_time = get_time(phi->rul) + time;
	while (get_time(phi->rul) < a_time)
		if (usleep(100) != 0)
			return ;
}

int		checkdie(t_philo *philo)
{
	t_rules	*rul;

	rul = philo->rul;
	if ((get_time(rul) - philo->last_eat) >= rul->time_to_die)
		return (DIE);
	return (ALIVE);
}

void ssleep(t_philo *philo)
{
	if (philo == NULL)
		ft_error(PTR_ERR, philo);
    print_status(philo, "is sleeping");
    ft_sleep(philo, philo->rul->time_to_sleep);
}

void think(t_philo *philo)
{
	if (philo == NULL)
		ft_error(PTR_ERR, philo);
	print_status(philo, "is thinking");
}

void	eat(t_philo *head)
{
	t_philo *philo;

	philo = head;
	pthread_mutex_lock(&(philo->left->mutex));
	pthread_mutex_lock(&(philo->right->mutex));
    print_status(philo, FORK);
    print_status(philo, FORK);

    // Yeme işlemi
	philo->eat_times += 1;
	philo->last_eat = get_time(philo->rul);
    print_status(philo, EAT);
    ft_sleep(philo, philo->rul->time_to_eat);

    // Çatalları bırak
    pthread_mutex_unlock(&(philo->left->mutex));
    pthread_mutex_unlock(&(philo->right->mutex));

	ssleep(philo);
	think(philo);
}

void	*bon_appetite(void *arg)
{
	t_philo	*phi;

	if (!arg)
		return (NULL);
	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(phi->rul->print_mutex));
		if (checkdie(phi) == DIE)
		{
			printf("%ld ms : %zu %s\n", get_time(phi->rul), phi->number, DEAD);
			free_philo_fork(phi);
			exit(1);
		}
		pthread_mutex_unlock(&(phi->rul->print_mutex));
		eat(phi);
	}
}

void launch(t_philo *head)
{
    t_philo *current = head;
    int i = 0;

	head->rul->base_time = get_time(head->rul);
    while (current->number > current->prev->number || i == 0)
    {
        if (pthread_create(&(current->thread), NULL, bon_appetite, (void *)current) != 0)
            ft_error(ERR_THRD_CR, head);
        current = current->next;
        i++;
    }

    current = head;
    i = 0;
    while (current->number > current->prev->number || i == 0)
    {
        if (pthread_join(current->thread, NULL) != 0)
            ft_error(ERR_THRD, head);
        current = current->next;
        i++;
    }
}
