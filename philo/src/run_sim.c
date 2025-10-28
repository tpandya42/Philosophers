/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:18:46 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/28 19:18:47 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Have to update time becauseee the death_checker might 
 * misread our philo as starving even before they run.. */
static int	create_philosopher_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->simulation_start = get_current_time_ms();
	while (i < sim->no_philo)
	{
		update_time(&sim->philos[i]);
		if (pthread_create(&sim->philos[i].life_thread, NULL, routine,
				&sim->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(sim->philos[i].life_thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_monitoring_threads(t_simulation *sim)
{
	if (pthread_create(&sim->monitor_thread, NULL, death_checker, sim) != 0)
		return (1);
	if (sim->max_eat_count > 0)
	{
		if (pthread_create(&sim->completion_thread, NULL, completion_watch,
				sim) != 0)
		{
			end_simulation(sim);
			pthread_join(sim->monitor_thread, NULL);
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
		while (i < sim->no_philo)
			pthread_join(sim->philos[i++].life_thread, NULL);
		return (1);
	}
	return (0);
}

int	terminate_simulation(t_simulation *sim)
{
	int	i;

	if (pthread_join(sim->monitor_thread, NULL) != 0)
		return (1);
	if (sim->max_eat_count > 0)
	{
		if (pthread_join(sim->completion_thread, NULL) != 0)
			return (1);
	}
	i = 0;
	while (i < sim->no_philo)
	{
		if (pthread_join(sim->philos[i].life_thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
