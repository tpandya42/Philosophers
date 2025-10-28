/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:48:24 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/06 14:48:25 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philos(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->no_philo)
	{
		pthread_mutex_destroy(&sim->philos[i].eat_time_mutex);
		pthread_mutex_destroy(&sim->philos[i].eat_count_mutex);
		i++;
	}
	free(sim->philos);
	sim->philos = NULL;
}

static void	destroy_sticks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->no_philo)
	{
		pthread_mutex_destroy(&sim->sticks[i]);
		i++;
	}
	free(sim->sticks);
	sim->sticks = NULL;
}

void	cleanup_simulation(t_simulation *sim)
{
	if (sim->philos)
		destroy_philos(sim);
	if (sim->sticks)
		destroy_sticks(sim);
	pthread_mutex_destroy(&sim->end_simulation_mutex);
	pthread_mutex_destroy(&sim->output_mutex);
}
