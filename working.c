#include "../philo.h"

void ft_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->rul->time_to_sleep * 1000);
}

void think(t_philo *philo)
{
	print_status(philo, "is thinking");
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
	philo->eat_times += 1;
    usleep(philo->rul->time_to_eat * 1000);

    // Çatalları bırak
	philo->left->status = 0;
	philo->right->status = 1;
    pthread_mutex_unlock(&(philo->left->mutex));
    pthread_mutex_unlock(&(philo->right->mutex));
	ft_sleep(philo);
	think(philo);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(philo->start_mutex);
    while (*(philo->start_flag) == 0)
    {
        pthread_cond_wait(philo->start_cond, philo->start_mutex);
    }
    pthread_mutex_unlock(philo->start_mutex);
	int i = 0;
    while (i < 200)
    {
		eat(philo);
		i++;
	}
	return (0);
}

void start_philosophers(t_philo *head)
{
    t_philo *current;
    int start_flag = 0;
    int num_philosophers = 0;

    // Philosopher sayısını hesapla
    current = head;
    do
    {
        num_philosophers++;
        current = current->next;
    } while (current != head);

    // Thread'leri başlat
    current = head;
    do
    {
        current->start_mutex = &start_mutex;
        current->start_cond = &start_cond;
        current->start_flag = &start_flag;
        if (pthread_create(&(current->thread), NULL, philosopher_routine, (void *)current) != 0)
        {
            ft_error(ERR_THRD);
        }
        current = current->next;
    } while (current != head);

    // Thread'leri başlatmak için mutex'i kilitle ve start_flag'i ayarla
    pthread_mutex_lock(&start_mutex);
    start_flag = 1;
    pthread_cond_broadcast(&start_cond);
    pthread_mutex_unlock(&start_mutex);

    // Thread'lerin bitmesini bekle
    current = head;
    do
    {
        pthread_join(current->thread, NULL);
        current = current->next;
    } while (current != head);

    // Mutex ve koşul değişkenini yok et
    pthread_mutex_destroy(&start_mutex);
    pthread_cond_destroy(&start_cond);
}


void	working(t_philo	*head)
{
	base_time(0);
	start_philosophers(head);
}