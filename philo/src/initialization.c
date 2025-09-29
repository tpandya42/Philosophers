#include "dining_philosophers.h"

static int	allocate_resources(t_simulation *sim)
{
	sim->thinkers = malloc(sizeof(t_thinker) * sim->thinker_count);
	if (!sim->thinkers)
		return (1);
	sim->utensils = malloc(sizeof(pthread_mutex_t) * sim->thinker_count);
	if (!sim->utensils)
	{
		free(sim->thinkers);
		return (1);
	}
	return (0);
}

static int	setup_utensils(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->thinker_count)
	{
		if (pthread_mutex_init(&sim->utensils[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->utensils[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	setup_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->thinker_count)
	{
		sim->thinkers[i].number = i + 1;
		sim->thinkers[i].bites_consumed = 0;
		sim->thinkers[i].finished_eating = false;
		sim->thinkers[i].sim = sim;
		if (pthread_mutex_init(&sim->thinkers[i].bite_time_mutex, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&sim->thinkers[i].bite_count_mutex, NULL) != 0)
		{
			pthread_mutex_destroy(&sim->thinkers[i].bite_time_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	setup_global_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->end_simulation_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->output_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->end_simulation_mutex);
		return (1);
	}
	return (0);
}

int	initialize_simulation(t_simulation *sim, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	sim->simulation_over = false;
	if (allocate_resources(sim))
		return (1);
	if (setup_utensils(sim))
	{
		free(sim->thinkers);
		free(sim->utensils);
		return (1);
	}
	if (setup_philosophers(sim))
	{
		cleanup_simulation(sim);
		return (1);
	}
	if (setup_global_mutexes(sim))
	{
		cleanup_simulation(sim);
		return (1);
	}
	return (0);
}
