#include "../philo.h"

long int base_time(int i)//0 set
{
	static long int base;
	long int	tmp;
	struct timeval tv;

    gettimeofday(&tv, NULL);
	tmp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (i == 0)
		base = tmp;
	return (base);
}

void print_status(t_philo *philo, const char *status)
{
    struct timeval tv;
	long int 	time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time_in_ms = time_in_ms - base_time(1);
    printf("%ld %zu %s\n", time_in_ms, philo->number, status);
}

void	eat(t_philo *head)
{
	t_philo *philo;

	philo = head;
	if (philo->left->status == 1 && philo->right->status == 1)
	{
		pthread_mutex_lock(&(philo->left->mutex));
    	pthread_mutex_lock(&(philo->right->mutex));
	}
	else
		return ;
	philo->left->status = 0;
    print_status(philo, "has taken a fork from left");
	philo->right->status = 0;
    print_status(philo, "has taken a fork from right");

    // Yeme işlemi
    print_status(philo, "is eating");
    usleep(philo->rul->time_to_eat * 1000);

    // Çatalları bırak
	
	philo->left->status = 0;
	philo->right->status = 1;
    pthread_mutex_unlock(&(philo->left->mutex));
    pthread_mutex_unlock(&(philo->right->mutex));
}

void sleep_and_think(t_philo *philo)
{
    // Uyuma işlemi
    print_status(philo, "is sleeping");
    usleep(philo->rul->time_to_sleep * 1000);

    // Düşünme işlemi
    print_status(philo, "is thinking");
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (500)
    {
        eat(philo);
        sleep_and_think(philo);
    }

    return (0);
}

void start_philosophers(t_philo *head)
{
    t_philo *current;

	current = head;
    do
    {
        if (pthread_create(&(current->thread), NULL, philosopher_routine, (void *)current) != 0)
        {
            ft_error(ERR_THRD);
        }
        current = current->next;
    } while (current != head);

    // Thread'lerin bitmesini bekle
    current = head;
    do
    {
        pthread_join(current->thread, NULL);
        current = current->next;
    } while (current != head);
}

void	working(t_philo	*head)
{
	base_time(0);
	start_philosophers(head);
}