/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:44:56 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:44:58 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	try_pick_stick(t_ph *philo, pthread_mutex_t *stick)
{
	while (!is_simulation_ended(philo))
	{
		if (pthread_mutex_trylock(stick) == 0)
			return (1);
		usleep(100);
	}
	return (0);
}

void	pick_up(t_ph *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	
	if (is_simulation_ended(philo))
		return ;
	
	// Always acquire forks in the same order to prevent deadlock
	// Use fork addresses to determine order
	if (&philo->left_stick->stick < &philo->right_stick->stick)
	{
		first_fork = &philo->left_stick->stick;
		second_fork = &philo->right_stick->stick;
	}
	else
	{
		first_fork = &philo->right_stick->stick;
		second_fork = &philo->left_stick->stick;
	}
	
	if (!try_pick_stick(philo, first_fork))
		return ;
	log_text(philo, FORK);
	
	if (!try_pick_stick(philo, second_fork))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	log_text(philo, FORK);
}

void	sleep_chunks(t_ph *philo, int time)
{
	int	chunk;

	while (time > 0 && !is_simulation_ended(philo))
	{
		if (time > 100)
			chunk = 100;
		else
			chunk = time;
		usleep(chunk);
		time -= chunk;
	}
}

void	drop_off(t_ph *philo)
{
	pthread_mutex_unlock(&philo->left_stick->stick);
	pthread_mutex_unlock(&philo->right_stick->stick);
	if (is_simulation_ended(philo))
		return ;
	log_text(philo, SLEEP);
	sleep_chunks(philo, philo->data->tts);
}

void	think(t_ph *philo)
{
	int	sleep_time;
	int	chunk;

	log_text(philo, THINK);
	sleep_time = 100;
	while (sleep_time > 0 && !is_simulation_ended(philo))
	{
		if (sleep_time > 10)
			chunk = 10;
		else
			chunk = sleep_time;
		usleep(chunk);
		sleep_time -= chunk;
	}
}
