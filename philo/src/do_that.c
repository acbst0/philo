/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_that.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:33:07 by abostano          #+#    #+#             */
/*   Updated: 2024/07/24 18:57:46 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ssleep(t_philo *philo)
{
	if (philo == NULL)
		ft_error(PTR_ERR, philo);
	print_status(philo, "is sleeping");
	ft_sleep(philo, philo->rul->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo == NULL)
		ft_error(PTR_ERR, philo);
	print_status(philo, "is thinking");
}

void	eat(t_philo *head)
{
	t_philo	*philo;

	philo = head;
	pthread_mutex_lock(&(philo->left->mutex));
	pthread_mutex_lock(&(philo->right->mutex));
	print_status(philo, FORK);
	print_status(philo, FORK);
	philo->eat_times += 1;
	philo->last_eat = get_time(philo->rul);
	ft_sleep(philo, philo->rul->time_to_eat);
	print_status(philo, EAT);
	pthread_mutex_unlock(&(philo->left->mutex));
	pthread_mutex_unlock(&(philo->right->mutex));
	ssleep(philo);
	think(philo);
}
