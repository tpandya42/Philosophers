#include "philo.h"

void *routine(void *arg)
{
	t_ph *philo = (t_ph *)arg;
	long timestamp;

	timestamp = get_time_in_ms() - philo->data->start_time;
	printf("%ld: Philosopher %d started!\n", timestamp, philo->id);
	fflush(stdout);

	usleep(500000);

	timestamp = get_time_in_ms() - philo->data->start_time;
	printf("%ld: Philosopher %d finished!\n", timestamp, philo->id);
	fflush(stdout);

	return NULL;
}

