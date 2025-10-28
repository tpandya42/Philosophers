/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:18:26 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/28 19:18:27 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_resources(t_simulation *sim)
{
	sim->philos = malloc(sizeof(t_thinker) * sim->no_philo);
	if (!sim->philos)
		return (1);
	sim->sticks = malloc(sizeof(pthread_mutex_t) * sim->no_philo);
	if (!sim->sticks)
	{
		free(sim->philos);
		return (1);
	}
	return (0);
}

static int	setup_chopsticks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->no_philo)
	{
		if (pthread_mutex_init(&sim->sticks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->sticks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	setup_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->no_philo)
	{
		sim->philos[i].philo_id = i + 1;
		sim->philos[i].times_eaten = 0;
		sim->philos[i].finished_eating = false;
		sim->philos[i].sim = sim;
		if (pthread_mutex_init(&sim->philos[i].eat_time_mutex, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&sim->philos[i].eat_count_mutex, NULL) != 0)
		{
			pthread_mutex_destroy(&sim->philos[i].eat_time_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	setup_global_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->end_simulation_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->output_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->end_simulation_mutex);
		return (1);
	}
	return (0);
}

int	initialize_simulation(t_simulation *sim, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	sim->simulation_over = false;
	if (allocate_resources(sim))
		return (1);
	if (setup_chopsticks(sim))
	{
		free(sim->philos);
		free(sim->sticks);
		return (1);
	}
	if (setup_philosophers(sim))
	{
		cleanup_simulation(sim);
		return (1);
	}
	if (setup_global_mutexes(sim))
	{
		cleanup_simulation(sim);
		return (1);
	}
	return (0);
}
