/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:28:21 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:28:23 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->philo[i].lock);
	time_since_last_meal = get_time_in_ms() - data->philo[i].last_eaten;
	pthread_mutex_unlock(&data->philo[i].lock);
	if (time_since_last_meal >= data->ttd)
	{
		pthread_mutex_lock(&data->death);
		if (!data->end)
		{
			data->end = true;
			log_text(&data->philo[i], DIE);
		}
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	return (0);
}

static int	check_all_done(t_data *data)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	while (i < data->num_ph)
	{
		pthread_mutex_lock(&data->philo[i].lock);
		if (data->philo[i].num_eat < data->must_eat)
			done = 0;
		pthread_mutex_unlock(&data->philo[i].lock);
		i++;
	}
	return (done);
}

void	*checker(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_ph)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (data->must_eat != -1 && check_all_done(data))
		{
			pthread_mutex_lock(&data->death);
			data->end = true;
			pthread_mutex_unlock(&data->death);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
