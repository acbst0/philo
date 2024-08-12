#include "../inc/header.h"

int	main(int ac, char **av)
{
	t_philo	**philo;
	t_rules	*rul;

	checkargs(ac, av);
	rul = init_rule(ac, av);
	philo = init_philo(rul);
}