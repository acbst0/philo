/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:09:37 by abostano          #+#    #+#             */
/*   Updated: 2024/05/23 12:01:33 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*head;
	t_rules	rul;

	if (argc == 5 || argc == 6)
	{
		head = init_philo(argv, &rul);
	}
	else
	{
		fprintf(stderr, "ERR\n");
	}
	return (0);
}
