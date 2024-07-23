#include "../inc/philo.h"

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

void	free_all(t_philo *head)
{
	t_philo *tmp;
	t_rules	*rul;

	rul = head->rul;
	tmp = head;
	while (tmp->id != 1)
		tmp = tmp->next;
	tmp->prev->next = NULL;
	tmp->left = NULL;
	tmp->prev = NULL;
	while (tmp)
	{
		head = tmp->next;
		pthread_mutex_destroy(&(tmp->right));
		free(tmp);
		tmp = head;
	}
	//pthread_mutex_destroy(rul->print_mutex);
	free(rul);
}

void	ft_error(char *str, t_philo *head)
{
	if (head != NULL)
		free_all(head);
	if (str == NULL)
		ft_putstr_fd(ERR_UNDF, 2);
	else
		ft_putstr_fd(str, 2);
	exit(1);
}