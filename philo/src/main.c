/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:53:16 by abostano          #+#    #+#             */
/*   Updated: 2024/08/21 11:53:17 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_philo(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].last_eat = 0;
		philo[i].par = p;
		philo[i].lf = &p->fork[i];
		philo[i].rf = 0;
	}
	return (0);
}

static int	init_params_mutex(t_params *p)
{
	int	i;

	i = -1;
	p->print_mutex = 0;
	p->fork = 0;
	p->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!p->print_mutex)
		return (error_msg("Error\nMutex death: malloc failed\n", p, 0, 1));
	p->fork = malloc(sizeof(pthread_mutex_t) * p->num);
	if (!p->fork)
		return (error_msg("Error\nMutex fork: malloc failed\n", p, 0, 1));
	if (pthread_mutex_init(p->print_mutex, NULL) == -1)
		return (error_msg("Error\nMutex init failed\n", p, 0, 1));
	while (++i < p->num)
		if (pthread_mutex_init(&p->fork[i], NULL) == -1)
			return (error_msg("Error\nMutex init failed\n", p, 0, 1));
	return (0);
}

static int	init_params(t_params *p, char **ag)
{
	int	mutex;

	mutex = -1;
	p->num = ft_atoi(ag[1]);
	p->t2d = ft_atoi(ag[2]);
	p->t2e = ft_atoi(ag[3]);
	p->t2s = ft_atoi(ag[4]);
	p->max_iter = -2;
	p->check_meal = 0;
	p->start = 0;
	p->ready = 0;
	if (ag[5])
	{
		p->check_meal = 1;
		p->max_iter = ft_atoi(ag[5]);
	}
	p->over = 0;
	if (p->num > 0)
		mutex = init_params_mutex(p);
	return (mutex || p->num <= 0 || p->t2d <= 0 || p->t2e <= 0
		|| p->t2s <= 0 || p->max_iter == 0);
}

int	main(int ac, char **ag)
{
	t_params	p;

	if ((ac != 5 && ac != 6) || init_params(&p, ag))
		return (error_msg("Error: invalid arguments\n", &p, 0, 1));
	if (philosophers(&p))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
