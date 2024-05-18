#include "philo.h"

int main(int ac, char *av[])
{
    philo_t *head;
    rules rul;

    if (ac == 5 || ac == 6)
	{
        head = init_philo(av, &rul);
    }
	else
	{
        fprintf(stderr, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
    }

    return 0;
}