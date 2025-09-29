#include "dining_philosophers.h"

bool	check_simulation_end(t_simulation *sim)
{
	bool	result;

	pthread_mutex_lock(&sim->end_simulation_mutex);
	result = sim->simulation_over;
	pthread_mutex_unlock(&sim->end_simulation_mutex);
	return (result);
}

void	end_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->end_simulation_mutex);
	sim->simulation_over = true;
	pthread_mutex_unlock(&sim->end_simulation_mutex);
}

static bool	check_philosopher_death(t_simulation *sim, int i)
{
	long	current_time;
	long	time_since_last_bite;

	current_time = get_current_time_ms();
	time_since_last_bite = current_time - get_bite_time(&sim->thinkers[i]);
	if (time_since_last_bite >= sim->death_timer)
	{
		end_simulation(sim);
		log_philosopher_action(&sim->thinkers[i], PERISH);
		return (true);
	}
	return (false);
}

void	*supervise_deaths(void *simulation_ptr)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)simulation_ptr;
	while (!check_simulation_end(sim))
	{
		i = 0;
		while (i < sim->thinker_count && !check_simulation_end(sim))
		{
			if (check_philosopher_death(sim, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static bool	all_philosophers_finished(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->thinker_count)
	{
		if (get_bite_count(&sim->thinkers[i]) < sim->required_bites)
			return (false);
		i++;
	}
	return (true);
}

void	*monitor_completion(void *simulation_ptr)
{
	t_simulation	*sim;

	sim = (t_simulation *)simulation_ptr;
	while (!check_simulation_end(sim) && sim->required_bites > 0)
	{
		if (all_philosophers_finished(sim))
		{
			end_simulation(sim);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
