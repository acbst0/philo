#include "../inc/header.h"

long int	get_time_pure()
{
	long int	tmp;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tmp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (tmp);
}

long int	get_time_ms(t_rules *rules)
{
	long int	tmp;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tmp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	tmp = tmp - rules->base_time;
	return (tmp);
}