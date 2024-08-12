#include "../inc/header.h"

long int	get_time_pure()
{
	long int	tmp;

	gettimeofday(&(rules->tv), NULL);
	tmp = (rules->tv.tv_sec * 1000) + (rules->tv.tv_usec / 1000);
	return (tmp);
}

long int	get_time(t_rules *rules)
{
	long int	tmp;

	gettimeofday(&(rules->tv), NULL);
	tmp = (rules->tv.tv_sec * 1000) + (rules->tv.tv_usec / 1000);
	tmp = tmp - rules->base_time;
	return (tmp);
}