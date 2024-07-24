/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:09:37 by abostano          #+#    #+#             */
/*   Updated: 2024/07/24 18:36:25 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*head;
	t_rules	*rul;

	if (argc == 5 || argc == 6)
	{
		rul = (t_rules *)malloc(sizeof(t_rules));
		head = init_philo(argv, rul);
		if (head)
		{
			launch(head);
			free_philo_fork(head);
		}
	}
	else
	{
		ft_error(ERR_NOF, NULL);
	}
	return (0);
}
