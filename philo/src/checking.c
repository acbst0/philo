/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:33:21 by abostano          #+#    #+#             */
/*   Updated: 2024/07/24 19:10:55 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	checkdie(t_philo *philo)
{
	t_rules	*rul;
	size_t	len;
	int		i;

	rul = philo->rul;
	while (philo->number != 1)
		philo = philo->next;
	len = philo->prev->number;
	i = 0;
	while (i < len)
	{
		if ((get_time(rul) - philo->last_eat - 1) >= rul->time_to_die)
		{
			printf("%ld ms : %zu %s\n", get_time(rul), philo->number, DEAD);
			free_philo_fork(philo);
			exit(1);
		}
		i++;
	}
}

void	checkeattimes(t_philo *philo)
{
	t_rules	*rul;
	t_philo	*tmp;
	int		flag;

	tmp = philo;
	rul = philo->rul;
	if (rul->per_eat == -1)
		return ;
	flag = 0;
	while (tmp != philo || flag == 0)
	{
		if (tmp->eat_times != rul->per_eat)
			return ;
		tmp = tmp->next;
	}
	free_philo_fork(philo);
	exit(1);
}
