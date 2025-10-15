/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:48:57 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/06 14:48:58 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dining_philosophers.h"

void	drop(t_thinker *philosopher)
{
	int	left_stick;
	int	right_stick;

	left_stick = philosopher->philo_id - 1;
	right_stick = philosopher->philo_id % philosopher->sim->no_philo;
	if (philosopher->philo_id % 2 == 1)
	{
		pthread_mutex_unlock(&philosopher->sim->sticks[right_stick]);
		pthread_mutex_unlock(&philosopher->sim->sticks[left_stick]);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->sim->sticks[left_stick]);
		pthread_mutex_unlock(&philosopher->sim->sticks[right_stick]);
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
	sleep(philosopher->sim->time_to_eat);
	increment_bites(philosopher);
	drop(philosopher);
}

void	go_sleep(t_thinker *philosopher)
{
	if (check_simulation_end(philosopher->sim))
		return ;
	logging(philosopher, SLEEP);
	sleep(philosopher->sim->time_to_sleep);
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
		go_sleep(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
