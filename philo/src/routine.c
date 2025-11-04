/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:18:37 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/28 19:18:40 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!take_sticks(philosopher))
		return ;
	if (check_simulation_end(philosopher->sim))
	{
		drop(philosopher);
		return ;
	}
	update_time(philosopher);
	logging(philosopher, EAT);
	sleep_sleep(philosopher->sim, philosopher->sim->time_to_sleep);
	increment_times_eaten(philosopher);
	drop(philosopher);
}

void	chill_out(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	logging(philosopher, SLEEP);
	sleep_sleep(philosopher->sim, philosopher->sim->time_to_sleep);
}

void	thinking(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	logging(philosopher, THINK);
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
			&& get_eat_count(philosopher) >= philosopher->sim->max_eat_count)
		{
			philosopher->finished_eating = true;
			break ;
		}
		chill_out(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
