#include "../inc/header.h"

void    *routine(void *ptr)
{
    t_philo *philo;
    t_rules *rul;

    philo = (t_philo *)ptr;
    rul = philo->rul;
    while (rul->alive == ALIVE)
    {
        eat(philo);
        if (rul->alive == ALLEAT)
            break ;
        if (rul->alive == ALIVE && check_all_philos_ate(philo->rul->philos) == ALLEAT)
        {
            rul->alive = ALLEAT;
            break;
        }
        if (rul->alive == ALIVE)
        {
            s_n_t(philo);
        }
    }
    return (NULL);
}

#include "../inc/header.h"

void    die_routine(t_philo **head, t_rules *rul)
{
    int i;

    while (rul->alive == ALIVE)
    {
        usleep(100);
        i = 0;
        while (head[i])
        {
            if (is_dead(head[i]) == DEAD)
            {
                print_status(head[i], "has died");
                rul->alive = DEAD;
                break;
            }
            i++;
        }
        // Tüm filozofların belirli sayıda yemek yediğini kontrol et
        if (rul->alive == ALIVE && check_all_philos_ate(head) == ALLEAT)
        {
            rul->alive = ALLEAT;
            break;
        }
    }
    // Yeme sayısına ulaşıldığında durumu yazdır
    if (rul->alive == ALLEAT)
    {
        pthread_mutex_lock(&(rul->print_mutex));
        printf("All philosophers have eaten %d times. Stopping simulation.\n", rul->et);
        pthread_mutex_unlock(&(rul->print_mutex));
    }
}

int	launch(t_philo **head)
{
	t_rules	*rul;
	int		i;

	i = 0;
	rul = head[0]->rul;
	rul->base_time = get_time_pure();
	while (head[i])
	{
		pthread_create(&(head[i]->thread), NULL, routine, head[i]);
		i++;
	}
	die_routine(head, rul);
	i = 0;
	while (head[i])
	{
		pthread_join(head[i]->thread, NULL);
		i++;
	}
	return (1);
}
