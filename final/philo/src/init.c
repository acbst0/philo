#include "../inc/philo.h"

void *set_details(t_philo *head)
{
	head->last_eat = 0;
	head->eat_times = 0;
	pthread_mutex_init(&(head->right), NULL);
	head->left = NULL;
	head->rul = NULL;
	head->next = NULL;
	head->prev = NULL;
}

void	add_to_end(t_philo *head, t_philo *added)
{
	t_philo	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = added;
	added->prev = tmp;
	added->left = &(tmp->right);
}

void	make_circle(t_philo *philo, t_rules *rul)
{
	t_philo *head;
	t_philo	*last;

	last = philo;
	while (last->next != NULL)
	{
		last->rul = rul;
		last = last->next;
	}
	last->rul = rul;
	head = philo;
	head->prev = last;
	last->next = head;
	head->left = &(last->right);
}
t_rules	*setrules(char **av)
{
	t_rules *rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&(rules->print_mutex), NULL);
	if (av[5] != NULL)
		rules->per_eat = ft_atoi(av[5]);
	else
		rules->per_eat = -1;
	rules->base_time = get_time_long();
	return (rules);
}

t_philo *philo_init(int numbers, t_rules *rul)
{
	t_philo	*head;
	t_philo	*tmp;
	int		i;

	i = 0;
	while (i < numbers)
	{
		tmp = (t_philo *)malloc(sizeof(t_philo));
		tmp->id = i + 1;
		set_details(tmp);
		if (i == 0)
			head = tmp;
		else
			add_to_end(head, tmp);
		i += 1;
	}
	make_circle(head, rul);
	return (head);
}

t_philo *init(char **av)
{
	t_rules *rules;
	t_philo *philo;
	int	n_o_p;

	philo = NULL;
	n_o_p = ft_atoi(av[1]);
	rules = setrules(av);
	philo = philo_init(n_o_p, rules);
	return (philo);
}