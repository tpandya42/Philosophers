#include "dining_philosophers.h"

void	take_sticks(t_thinker *philosopher)
{
	int	left_utensil;
	int	right_utensil;

	if (check_simulation_end(philosopher->sim))
		return ;
	left_utensil = philosopher->philo_id - 1;
	right_utensil = philosopher->philo_id % philosopher->sim->no_philo;
	if (philosopher->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&philosopher->sim->sticks[left_utensil]);
		log(philosopher, STICK);
		if (check_simulation_end(philosopher->sim))
		{
			pthread_mutex_unlock(&philosopher->sim->sticks[left_utensil]);
			return ;
		}
		pthread_mutex_lock(&philosopher->sim->sticks[right_utensil]);
		log(philosopher, STICK);
	}
	else
	{
		pthread_mutex_lock(&philosopher->sim->sticks[right_utensil]);
		log(philosopher, STICK);
		if (check_simulation_end(philosopher->sim))
		{
			pthread_mutex_unlock(&philosopher->sim->sticks[right_utensil]);
			return ;
		}
		pthread_mutex_lock(&philosopher->sim->sticks[left_utensil]);
		log(philosopher, STICK);
	}
}

void	drop(t_thinker *philosopher)
{
	int	left_utensil;
	int	right_utensil;

	left_utensil = philosopher->philo_id - 1;
	right_utensil = philosopher->philo_id % philosopher->sim->no_philo;
	if (philosopher->philo_id % 2 == 1)
	{
		pthread_mutex_unlock(&philosopher->sim->sticks[right_utensil]);
		pthread_mutex_unlock(&philosopher->sim->sticks[left_utensil]);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->sim->sticks[left_utensil]);
		pthread_mutex_unlock(&philosopher->sim->sticks[right_utensil]);
	}
}

void	eatting(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	take_sticks(philosopher);
	if (check_simulation_end(philosopher->sim))
	{
		drop(philosopher);
		return ;
	}
	update_time(philosopher);
	log(philosopher, EAT);
	sleep(philosopher->sim->time_to_eat);
	increment_bites(philosopher);
	drop(philosopher);
}

void	take_rest(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	log(philosopher, SLEEP);
	sleep(philosopher->sim->time_to_sleep);
}

void	thinking(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	log(philosopher, THINK);
	usleep(1000);
}

void	*routine(void *philosopher_ptr)
{
	t_thinker	*philosopher;

	philosopher = (t_thinker *)philosopher_ptr;
	if (philosopher->philo_id % 2 == 0)
		usleep(1000);
	while (!check_simulation_end(philosopher->sim)
		&& !philosopher->finished_eating)
	{
		eatting(philosopher);
		if (check_simulation_end(philosopher->sim))
			break ;
		if (philosopher->sim->max_eat_count > 0
			&& get_bite_count(philosopher) >= philosopher->sim->max_eat_count)
		{
			philosopher->finished_eating = true;
			break ;
		}
		take_rest(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
