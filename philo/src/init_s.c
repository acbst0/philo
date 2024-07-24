/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:04:13 by abostano          #+#    #+#             */
/*   Updated: 2024/07/24 11:58:09 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	add_details(t_philo *new, t_forks *new_fork)
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
	pthread_mutex_init(&(new_fork->mutex), NULL);
	new_fork->status = 1;
	new_fork->next = NULL;
	new->last_eat = 0;
	new->alive = ALIVE;
	new->next = NULL;
	new->rul = NULL;
	new->eat_times = 0;
}

void	add_philo(t_philo **head)
{
	t_philo	*tmp;
	t_philo	*new;
	t_forks	*new_fork;

	tmp = *head;
	new_fork = (t_forks *)malloc(sizeof(t_forks));
	new = (t_philo *)malloc(sizeof(t_philo));
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

void	set_rules(char **av, t_rules *rul)
{
	rul->base_time = 0;
	rul->time_to_die = ft_atoi(av[2]);
	rul->time_to_eat = ft_atoi(av[3]);
	rul->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&(rul->print_mutex), NULL);
	if (av[5] == NULL)
		rul->per_eat = -1;
	else
		rul->per_eat = ft_atoi(av[5]);
}

void	make_circle(t_philo **head, t_rules *rul)
{
	t_philo	*first;
	t_philo	*last;

	first = *head;
	last = *head;
	while (last->next)
	{
		if (last->rul == NULL)
			last->rul = rul;
		last = last->next;
	}
	last->rul = rul;
	first->left = last->right;
	last->next = first;
	first->prev = last;
	first->left->next = first->right;
	first->right->prev = first->left;
}

t_philo	*init_philo(char **av, t_rules *rul)
{
	int		number_of;
	int		i;
	t_philo	*head;

	head = NULL;
	i = 0;
	number_of = ft_atoi(av[1]);
	set_rules(av, rul);
	while (i < number_of)
	{
		add_philo(&head);
		i++;
	}
	make_circle(&head, rul);
	return (head);
}
