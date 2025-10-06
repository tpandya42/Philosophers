/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:31:41 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/06 19:31:42 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dining_philosophers.h"

static bool	take_sticks_odd(t_thinker *philosopher, int left, int right)
{
	pthread_mutex_lock(&philosopher->sim->sticks[left]);
	logging(philosopher, STICK);
	if (check_simulation_end(philosopher->sim))
	{
		pthread_mutex_unlock(&philosopher->sim->sticks[left]);
		return (false);
	}
	pthread_mutex_lock(&philosopher->sim->sticks[right]);
	logging(philosopher, STICK);
	return (true);
}

static bool	take_sticks_even(t_thinker *philosopher, int left, int right)
{
	pthread_mutex_lock(&philosopher->sim->sticks[right]);
	logging(philosopher, STICK);
	if (check_simulation_end(philosopher->sim))
	{
		pthread_mutex_unlock(&philosopher->sim->sticks[right]);
		return (false);
	}
	pthread_mutex_lock(&philosopher->sim->sticks[left]);
	logging(philosopher, STICK);
	return (true);
}

bool	take_sticks(t_thinker *philosopher)
{
	int	left;
	int	right;

	if (check_simulation_end(philosopher->sim))
		return (false);
	left = philosopher->philo_id - 1;
	right = philosopher->philo_id % philosopher->sim->no_philo;
	if (philosopher->philo_id % 2 == 1)
		return (take_sticks_odd(philosopher, left, right));
	else
		return (take_sticks_even(philosopher, left, right));
}

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
