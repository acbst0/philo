/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:03:21 by abostano          #+#    #+#             */
/*   Updated: 2024/05/23 12:53:12 by abostano         ###   ########.fr       */
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

void	ft_error(char *str)
{
	if (str == NULL)
		ft_putstr_fd("ERROR", 2);
	else
		ft_putstr_fd(str, 2);
}

void	free_philo_fork(t_philo *head)
{
	t_philo	*tmp;

	while (head && head->next != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->right);
		free(tmp);
		tmp = NULL;
	}
}
