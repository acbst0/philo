#include "../philo.h"

int	create_thr(t_philo	*head)
{
	t_philo	*tmp;

	tmp = head;
	while (head->number > head->prev->number)
	{
		if(pthread_create(&head->thread, NULL, whatimgonnado, head) != 0)
		{
			free_philo_fork(head);
        	ft_error(ERR_THRD);
			return (-1);
    	}
	}
}

void	working(t_philo	*head, t_rules rules)
{

}

void	*whatimgonnado(void *arg)
{
	t_philo	*head;

	head = (t_philo *)arg;
}
