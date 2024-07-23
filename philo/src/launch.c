#include "../philo.h"

void check_am_i_died(t_philo *philo)
{
	t_rules *rul;
    long int current_time;

	rul = philo->rul;
    if (philo == NULL || philo->rul == NULL)
		ft_error(PTR_ERR, philo);
    current_time = get_time(philo->rul);
    if (current_time - philo->last_eat > philo->rul->time_to_die)
    {
        print_status(philo, "is died");
		free_philo_fork(philo);
        exit(1);
    }
}

void ssleep(t_philo *philo)
{
	if (philo == NULL)
		ft_error(PTR_ERR, philo);
    print_status(philo, "is sleeping");
    usleep(philo->rul->time_to_sleep * 1000);
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
    print_status(philo, "has taken a fork from left");
    print_status(philo, "has taken a fork from right");

    // Yeme işlemi
    print_status(philo, EAT);
	philo->eat_times += 1;
	philo->last_eat = get_time(philo->rul);
    usleep(philo->rul->time_to_eat * 1000);

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
		check_am_i_died(phi);
		eat(phi);
	}
}

void launch(t_philo *head)
{
    t_philo *current = head;
    int i = 0;

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
