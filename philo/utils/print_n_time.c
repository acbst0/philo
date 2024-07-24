/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_n_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:18:27 by abostano          #+#    #+#             */
/*   Updated: 2024/07/24 16:19:28 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long int	get_time(t_rules *rules)
{
	long int	tmp;

	gettimeofday(&(rules->tv), NULL);
	tmp = (rules->tv.tv_sec * 1000) + (rules->tv.tv_usec / 1000);
	tmp = tmp - rules->base_time;
	return (tmp);
}

void	print_status(t_philo *philo, const char *status)
{
	long int	time_in_ms;

	if (philo == NULL || !philo->rul)
		ft_error(PTR_ERR, philo);
	pthread_mutex_lock(&(philo->rul->print_mutex));
	time_in_ms = get_time(philo->rul);
	printf("%ld ms : %zu %s\n", time_in_ms, philo->number, status);
	pthread_mutex_unlock(&(philo->rul->print_mutex));
}
