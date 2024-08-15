#include "../inc/header.h"

void    print_status(t_philo *philo, const char *txt)
{
    long int    time_in_ms;
    t_rules     *rul;

    rul = philo->rul;
    pthread_mutex_lock(&(rul->print_mutex));
    time_in_ms = get_time_ms(rul);
    if (rul->alive == DEAD && ft_strcmp(txt, "has died") != 0)
    {
        pthread_mutex_unlock(&(rul->print_mutex));
        return;
    }
    if (rul->alive == ALLEAT && ft_strcmp(txt, "is eating") != 0)
    {
        pthread_mutex_unlock(&(rul->print_mutex));
        return;
    }
    printf("%ld ms : %zu %s\n", time_in_ms, philo->number, txt);
    pthread_mutex_unlock(&(rul->print_mutex));
}
