#include "dining_philosophers.h"

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	if (sim->philos)
	{
		i = 0;
		while (i < sim->no_philo)
		{
			pthread_mutex_destroy(&sim->philos[i].eat_time_mutex);
			pthread_mutex_destroy(&sim->philos[i].eat_count_mutex);
			i++;
		}
		free(sim->philos);
		sim->philos = NULL;
	}
	if (sim->sticks)
	{
		i = 0;
		while (i < sim->no_philo)
		{
			pthread_mutex_destroy(&sim->sticks[i]);
			i++;
		}
		free(sim->sticks);
		sim->sticks = NULL;
	}
	pthread_mutex_destroy(&sim->end_simulation_mutex);
	pthread_mutex_destroy(&sim->output_mutex);
}
