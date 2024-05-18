#include "philo.h"

void add_details(philo_t *new, forks_t *new_fork)
{
    if (new->prev == NULL)
	{
        new->number = 1;
        new->left = NULL;
        new_fork->prev = NULL;
    }
	else
	{
        new->number = new->prev->number + 1;
        new->left = new->prev->right;
        new->prev->right->next = new_fork;
        new_fork->prev = new->prev->right;
    }
    new_fork->fork_number = new->number;
    new_fork->status = 1;
    new_fork->next = NULL;
    new->last_eat = 0;
    new->last_thinking = 0;
    new->last_sleep = 0;
    new->next = NULL;
}

void add_philo(philo_t **head, char *av[])
{
    philo_t *tmp = *head;
    philo_t *new = (philo_t *)malloc(sizeof(philo_t));
    forks_t *new_fork = (forks_t *)malloc(sizeof(forks_t));

    if (!new || !new_fork)
	{
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new->right = new_fork;

    if (tmp == NULL)
	{
        *head = new;
        new->prev = NULL;
    }
	else
	{
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
    add_details(new, new_fork);
}

void set_rules(char **av, rules *rul)
{
    rul->time_to_die = ft_atoi(av[2]);
    rul->time_to_eat = ft_atoi(av[3]);
    rul->time_to_sleep = ft_atoi(av[4]);
    if (av[5] == NULL)
        rul->per_eat = -1; // NULL yerine -1 kullanmak daha güvenli
    else
        rul->per_eat = ft_atoi(av[5]);
}

void make_circle(philo_t **head)
{
	philo_t *first;
	philo_t *last;

	first = *head;
	last = *head;
	while (last->next)
	{
		last = last->next;
	}
	first->left = last->right;
	last->next = first;
	first->prev = last;
	first->left->next = first->right;
	first->right->prev = first->left;
}

philo_t *init_philo(char **av, rules *rul)
{
    int number_of;
    int i;
    philo_t *head;

	head = NULL;
	i = 0;
    number_of = ft_atoi(av[1]);
    set_rules(av, rul);
    
    while (i < number_of)
	{
        add_philo(&head, av);
		i++;
    }
	make_circle(&head);
    return head;
}
