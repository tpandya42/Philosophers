#include "dining_philosophers.h"

static int	create_philosopher_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->simulation_start = get_current_time_ms();
	while (i < sim->thinker_count)
	{
		update_bite_time(&sim->thinkers[i]);
		if (pthread_create(&sim->thinkers[i].life_thread, NULL,
				philosopher_routine, &sim->thinkers[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(sim->thinkers[i].life_thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_monitoring_threads(t_simulation *sim)
{
	if (pthread_create(&sim->supervisor_thread, NULL, supervise_deaths,
			sim) != 0)
		return (1);
	if (sim->required_bites > 0)
	{
		if (pthread_create(&sim->completion_thread, NULL, monitor_completion,
				sim) != 0)
		{
			end_simulation(sim);
			pthread_join(sim->supervisor_thread, NULL);
			return (1);
		}
	}
	return (0);
}

int	launch_simulation(t_simulation *sim)
{
	int	i;

	if (create_philosopher_threads(sim))
		return (1);
	if (create_monitoring_threads(sim))
	{
		i = 0;
		end_simulation(sim);
		while (i < sim->thinker_count)
			pthread_join(sim->thinkers[i++].life_thread, NULL);
		return (1);
	}
	return (0);
}

int	terminate_simulation(t_simulation *sim)
{
	int	i;

	if (pthread_join(sim->supervisor_thread, NULL) != 0)
		return (1);
	if (sim->required_bites > 0)
	{
		if (pthread_join(sim->completion_thread, NULL) != 0)
			return (1);
	}
	i = 0;
	while (i < sim->thinker_count)
	{
		if (pthread_join(sim->thinkers[i].life_thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
