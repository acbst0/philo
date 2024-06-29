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
    printf("%ld ms : %zu %s\n", time_in_ms, philo->number, status);
}

void ft_sleep(t_philo *philo)
{
    // Uyuma işlemi
    print_status(philo, "is sleeping");
    usleep(philo->rul->time_to_sleep * 1000);
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
}

void think(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(1000);
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
    while (1)
    {
		eat(philo);
		think(philo);
/* 
		if ((base_time(1) - philo->last_eat) < philo->rul->time_to_eat)
		{
			print_status(philo, "is eating");
		}
		else
		{
        	if ((base_time(1) - philo->last_eat < philo->rul->time_to_die / 2) || base_time(1) < philo->rul->time_to_die)
			{
				eat(philo);
			}
			think(philo);
		}
		 */
    }
    return (0);
}

void start_philosophers(t_philo *head)
{
    t_philo *current;
    pthread_mutex_t start_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t start_cond = PTHREAD_COND_INITIALIZER;
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