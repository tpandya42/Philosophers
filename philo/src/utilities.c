/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:49:16 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/06 14:49:17 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	logging(t_thinker *philosopher, t_action action)
{
	long		timestamp;
	const char	*action_str;

	if (action == STICK)
		action_str = "has taken a fork";
	else if (action == EAT)
		action_str = "is eating";
	else if (action == SLEEP)
		action_str = "is sleeping";
	else if (action == THINK)
		action_str = "is thinking";
	else if (action == DIE)
		action_str = "died";
	else
		return ;
	pthread_mutex_lock(&philosopher->sim->output_mutex);
	if (!check_simulation_end(philosopher->sim) || action == DIE)
	{
		timestamp = get_current_time_ms() - philosopher->sim->simulation_start;
		printf("%ld %d %s\n", timestamp, philosopher->philo_id, action_str);
	}
	pthread_mutex_unlock(&philosopher->sim->output_mutex);
}

unsigned int	sleep_sleep(t_simulation *sim, long long sleep_time)
{
	long long	wakey_wakey;

	wakey_wakey = get_current_time_ms() + sleep_time;
	while (get_current_time_ms() < wakey_wakey)
	{
		if (check_simulation_end(sim))
			break ;
		usleep(100);
	}
	return (0);
}
