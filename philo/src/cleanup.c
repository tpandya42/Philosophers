#include "dining_philosophers.h"

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	if (sim->thinkers)
	{
		i = 0;
		while (i < sim->thinker_count)
		{
			pthread_mutex_destroy(&sim->thinkers[i].bite_time_mutex);
			pthread_mutex_destroy(&sim->thinkers[i].bite_count_mutex);
			i++;
		}
		free(sim->thinkers);
		sim->thinkers = NULL;
	}
	if (sim->utensils)
	{
		i = 0;
		while (i < sim->thinker_count)
		{
			pthread_mutex_destroy(&sim->utensils[i]);
			i++;
		}
		free(sim->utensils);
		sim->utensils = NULL;
	}
	pthread_mutex_destroy(&sim->end_simulation_mutex);
	pthread_mutex_destroy(&sim->output_mutex);
}
