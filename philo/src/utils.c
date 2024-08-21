/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:53:29 by abostano          #+#    #+#             */
/*   Updated: 2024/08/21 11:53:30 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_msg(char *s, t_params *par, t_philo *p, int malloc)
{
	if (malloc)
	{
		if (par->print_mutex)
			free(par->print_mutex);
		if (par->fork)
			free(par->fork);
		if (p)
			free(p);
	}
	return (printf("%s", s));
}

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(p->par->print_mutex);
	if (p->par->over)
	{
		pthread_mutex_unlock(p->par->print_mutex);
		return ;
	}
	printf("%ldms %d %s\n", time_now() - p->thread_start,
		p->id, action);
	pthread_mutex_unlock(p->par->print_mutex);
}

void	final_print(int alive)
{
	printf("						\n");
	if (alive)
		printf("	:) no one died today	\n");
	else
		printf("	:(		\n");
	printf("						\n");
}
