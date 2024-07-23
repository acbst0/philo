#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo	*head;

	if (ac == 5 || ac == 6)
	{
		head = init(av);
		launch(head);
	}
}