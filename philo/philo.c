/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:09:37 by abostano          #+#    #+#             */
/*   Updated: 2024/05/28 12:08:52 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void test_print(t_philo *head)
{
	int i = 20;
	while (1)
	{
		printf("<- %ld Philo -> %d Fork ", head->number, head->right->fork_number);
		head = head->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*head;
	t_rules	*rul;

	if (argc == 5 || argc == 6)
	{
		rul = (t_rules *)malloc(sizeof(t_rules));
		head = init_philo(argv, rul);
		//test_print(head);
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
