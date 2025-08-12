#include "philo.c"

void	*routine(void *arg)
{
	t_ph *philo = (t_ph *)arg;
	fprintf(stderr ,"Started\n", philo->id);
	return (NULL);
}
