#include "../philo.h"

void	ft_sleep(t_philo *phi, unsigned long time)
{
	unsigned long	a_time;

	a_time = get_time(phi->rul) + time;
	while (get_time(phi->rul) < a_time)
		if (usleep(100) != 0)
			return ;
}

void	checkeattimes(t_philo *philo)
{
	t_philo *tmp;
	int rule;
	int i;

	tmp = philo;
	i = 0;
	rule = philo->rul->per_eat;
	if (rule == -1)
		return ;
	while (tmp != philo || i == 0)
	{
		if (tmp->eat_times != rule)
			return ;
		i++;
		tmp = tmp->next;
	}
	free_philo_fork(philo);
	exit(1);
}

void	checkdie(t_philo *philo)
{
	t_rules	*rul;

	rul = philo->rul;
	pthread_mutex_lock(&(rul->print_mutex));
	if (get_time(rul) - philo->last_eat - rul->time_to_die > 0)
	{
		printf("%ld ms : %zu %s\n", get_time(rul), philo->number, "died");
		free_philo_fork(philo);
		exit(1);
	}
	pthread_mutex_unlock(&(rul->print_mutex));
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
	philo->eat_times += 1;
	philo->last_eat = get_time(philo->rul);
	checkeattimes(philo);
    ft_sleep(philo, philo->rul->time_to_eat);
    print_status(philo, EAT);
    pthread_mutex_unlock(&(philo->left->mutex));
    pthread_mutex_unlock(&(philo->right->mutex));
}

void	*bon_appetite(void *arg)
{
	t_philo	*phi;

	if (!arg)
		return (NULL);
	phi = (t_philo *)arg;
	while (1)
	{
		checkdie(phi);
		eat(phi);
		ssleep(phi);
		think(phi);
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
