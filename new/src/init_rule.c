#include "../inc/header.h"

t_rules	*init_rule(int ac, char **av)
{
	t_rules	*rul;

	rul = (t_rules *)malloc(sizeof(t_rules));
	rul->nop = ft_atoi(av[1]);
	rul->t2d = ft_atoi(av[2]);
	rul->t2e = ft_atoi(av[3]);
	rul->t2s = ft_atoi(av[4]);
	if (ac == 6)
		rul->et = ft_atoi(av[5]);
	else
		rul->et = -1;
	pthread_mutex_init(&(rul->print_mutex), NULL);
	rul->alive = ALIVE;
	rul->base_time = 0;
}
