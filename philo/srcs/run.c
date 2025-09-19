/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:31:14 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:31:15 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	join_threads(pthread_t *threads, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_ph)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			write(2, "Failed to join thread\n", 21);
			while (i < data->num_ph)
				pthread_join(threads[i++], NULL);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	create_threads(pthread_t *threads, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_ph)
	{
		if (pthread_create(&threads[i], NULL, routine, &data->philo[i]) != 0)
		{
			write(2, "Can't make threads\n", 19);
			while (--i >= 0)
				pthread_join(threads[i], NULL);
			free(threads);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	run(t_data *data)
{
	pthread_t	*threads;
	pthread_t	check_death;

	threads = malloc(sizeof(pthread_t) * data->num_ph);
	if (!threads)
		return (FAILURE);
	if (create_threads(threads, data) == FAILURE)
		return (free(threads), FAILURE);
	if (pthread_create(&check_death, NULL, checker, data) != 0)
	{
		write(2, "Can't create monitor thread\n", 28);
		data->end = 1;
		join_threads(threads, data);
		free(threads);
		return (FAILURE);
	}
	pthread_join(check_death, NULL);
	usleep(10000);
	if (join_threads(threads, data) == FAILURE)
		return (free(threads), FAILURE);
	free(threads);
	return (SUCCESS);
}
