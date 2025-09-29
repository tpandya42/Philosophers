#include "dining_philosophers.h"

void	acquire_utensils(t_thinker *philosopher)
{
	int	left_utensil;
	int	right_utensil;

	if (check_simulation_end(philosopher->sim))
		return ;
	
	left_utensil = philosopher->number - 1;
	right_utensil = philosopher->number % philosopher->sim->thinker_count;
	
	// Prevent deadlock: odd philosophers take left first, even take right first
	if (philosopher->number % 2 == 1)
	{
		pthread_mutex_lock(&philosopher->sim->utensils[left_utensil]);
		log_philosopher_action(philosopher, TAKE_UTENSIL);
		if (check_simulation_end(philosopher->sim))
		{
			pthread_mutex_unlock(&philosopher->sim->utensils[left_utensil]);
			return ;
		}
		pthread_mutex_lock(&philosopher->sim->utensils[right_utensil]);
		log_philosopher_action(philosopher, TAKE_UTENSIL);
	}
	else
	{
		pthread_mutex_lock(&philosopher->sim->utensils[right_utensil]);
		log_philosopher_action(philosopher, TAKE_UTENSIL);
		if (check_simulation_end(philosopher->sim))
		{
			pthread_mutex_unlock(&philosopher->sim->utensils[right_utensil]);
			return ;
		}
		pthread_mutex_lock(&philosopher->sim->utensils[left_utensil]);
		log_philosopher_action(philosopher, TAKE_UTENSIL);
	}
}

void	release_utensils(t_thinker *philosopher)
{
	int	left_utensil;
	int	right_utensil;

	left_utensil = philosopher->number - 1;
	right_utensil = philosopher->number % philosopher->sim->thinker_count;
	
	// Release in reverse order of acquisition
	if (philosopher->number % 2 == 1)
	{
		pthread_mutex_unlock(&philosopher->sim->utensils[right_utensil]);
		pthread_mutex_unlock(&philosopher->sim->utensils[left_utensil]);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->sim->utensils[left_utensil]);
		pthread_mutex_unlock(&philosopher->sim->utensils[right_utensil]);
	}
}

void	consume_meal(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	
	acquire_utensils(philosopher);
	
	if (check_simulation_end(philosopher->sim))
	{
		release_utensils(philosopher);
		return ;
	}
	
	update_bite_time(philosopher);
	log_philosopher_action(philosopher, CONSUME_FOOD);
	precise_sleep(philosopher->sim->eating_duration);
	increment_bite_count(philosopher);
	
	release_utensils(philosopher);
}

void	take_rest(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	
	log_philosopher_action(philosopher, REST);
	precise_sleep(philosopher->sim->sleeping_duration);
}

void	think_deeply(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	
	log_philosopher_action(philosopher, CONTEMPLATE);
	usleep(1000); // Brief thinking time to reduce CPU usage
}

void	*philosopher_routine(void *philosopher_ptr)
{
	t_thinker	*philosopher;

	philosopher = (t_thinker *)philosopher_ptr;
	
	// Even numbered philosophers start with a small delay to reduce contention
	if (philosopher->number % 2 == 0)
		usleep(1000);
	
	while (!check_simulation_end(philosopher->sim) && !philosopher->finished_eating)
	{
		consume_meal(philosopher);
		
		if (check_simulation_end(philosopher->sim))
			break ;
		
		// Check if this philosopher has eaten enough
		if (philosopher->sim->required_bites > 0 && 
			get_bite_count(philosopher) >= philosopher->sim->required_bites)
		{
			philosopher->finished_eating = true;
			break ;
		}
		
		take_rest(philosopher);
		think_deeply(philosopher);
	}
	
	return (NULL);
}