/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:28:20 by abostano          #+#    #+#             */
/*   Updated: 2024/08/12 16:12:37 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_sleep(t_philo *phi, unsigned long time)
{
	unsigned long	a_time;

	a_time = get_time(phi->rul) + time;
	while (get_time(phi->rul) < a_time)
		if (usleep(100) != 0)
			return ;
}

void	*bon_appetite(void *arg)
{
	t_philo	*phi;

	if (!arg)
		return (NULL);
	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(phi->rul->print_mutex));
		checkdie(phi);
		checkeattimes(phi);
		pthread_mutex_unlock(&(phi->rul->print_mutex));
		eat(phi);
	}
}

void	launch(t_philo *head)
{
	t_philo	*current;
	int		i;

	current = head;
	i = 0;
	head->rul->base_time = get_time(head->rul);
	while (current->number > current->prev->number || i == 0)
	{
		if (pthread_create(&(current->thread), NULL,
				bon_appetite, (void *)current) != 0)
			ft_error(ERR_THRD_CR, head);
		current = current->next;
		i++;
	}
	current = head;
	i = 0;
	while (current->number > current->prev->number || i == 0)
	{
		if (pthread_join(current->thread, NULL) != 0)
			ft_error(ERR_THRD, head);
		current = current->next;
		i++;
	}
}
