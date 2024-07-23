/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:03:21 by abostano          #+#    #+#             */
/*   Updated: 2024/05/28 11:30:22 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *a)
{
	size_t	i;

	i = 0;
	while (a[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_error(char *str, t_philo *head)
{
	if (head != NULL)
		free_philo_fork(head);
	if (str == NULL)
		ft_putstr_fd("ERROR", 2);
	else
		ft_putstr_fd(str, 2);
	exit(1);
}

void	free_philo_fork(t_philo *head)
{
	t_rules	*rul;
	t_forks	*forks;
	t_philo *tmp;

	if (!head)
		return ;
	while (head->number != 1)
		head = head->next;
	tmp = head->prev;
	rul = head->rul;
	forks = head->right;
	while (head != tmp)
	{
		head = head->next;
		free(head->prev);
		pthread_mutex_destroy(&(forks->mutex));
		forks = forks->next;
		free(forks->prev);
	}
	pthread_mutex_destroy(&(forks->mutex));
	free(forks);
	free(tmp);//head olabilir                                         
	free(rul);
	return ;
}
