/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:53:22 by abostano          #+#    #+#             */
/*   Updated: 2024/08/21 15:46:20 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	someone_died(t_philo *p)
{
	print_routine(p, DIE);
	p->par->over = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->lf);
	pthread_mutex_unlock(p->rf);
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	pthread_mutex_lock(p->par->print_mutex);
	now = time_now() - p->last_eat;
	if (now >= p->par->t2d)
	{
		p->par->over = 1;
		pthread_mutex_unlock(p->par->print_mutex);
		return (someone_died(p));
	}
	pthread_mutex_unlock(p->par->print_mutex);
	return (0);
}

void	ft_sleep_and_think(t_philo *p)
{
	ft_usleep(p->par->t2s);
	print_routine(p, SLEEP);
	print_routine(p, THINK);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->lf);
	print_routine(p, FORK);
	pthread_mutex_lock(p->rf);
	print_routine(p, FORK);
	p->last_eat = time_now();
	ft_usleep(p->par->t2e);
	print_routine(p, EAT);
	p->iter_num++;
	pthread_mutex_unlock(p->lf);
	pthread_mutex_unlock(p->rf);
}

void	*thread_routine(void *job)
{
	t_philo	*p;

	p = (t_philo *)job;
	while (!p->par->ready)
		continue ;
	if (p->id & 1)
		ft_usleep(p->par->t2e * 0.9 + 1);
	while (!p->par->over)
	{
		ft_eat(p);
		ft_sleep_and_think(p);
	}
	return (NULL);
}
