#include "../inc/philo.h"

int		checkdie(t_philo *philo)
{
	t_rules	*rul;

	rul = philo->rul;
	if ((get_time(rul) - philo->last_eat) > rul->time_to_die)
		return (DEAD);
	return (ALIVE);
}

void	sleeping_and_thinking(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->rul->time_to_sleep * 1000);
	print_status(philo, THINK);
}

void	eat(t_philo *head)
{
	pthread_mutex_lock(head->left);
	print_status(head, FORK);
	pthread_mutex_lock(&(head->right));
	print_status(head, FORK);
	print_status(head, EAT);
	usleep(head->rul->time_to_eat * 1000);
	pthread_mutex_unlock(head->left);
	pthread_mutex_unlock(&(head->right));
	sleeping_and_thinking(head);
}

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (checkdie(philo) == DEAD)
		{
			print_status(philo, DIE);
			free_all(philo);
			exit(1);
		}
		eat(philo);
	}
}

void launch(t_philo *head)
{
	t_philo	*current;

	int i = 0;
	current = head;
    while (current != head || i == 0)
    {
        if (pthread_create(&(current->thread), NULL, routine, (void *)current) != 0)
            ft_error(ERR_CTRD, head);
        current = current->next;
        i++;
    }
    current = head;
    i = 0;
    while (current != head || i == 0)
    {
        if (pthread_join(current->thread, NULL) != 0)
            ft_error(ERR_JTRD, head);
        current = current->next;
        i++;
    }
}