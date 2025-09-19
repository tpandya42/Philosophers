/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:28:48 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:28:49 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_last_eaten(t_ph *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_eaten = get_time_in_ms();
	pthread_mutex_unlock(&philo->lock);
}

static void	update_num_eat(t_ph *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->num_eat++;
	pthread_mutex_unlock(&philo->lock);
}

void	eating(t_ph *philo)
{
	if (philo->data->end)
		return ;
	pick_up(philo);
	if (philo->data->end)
		return ;
	update_last_eaten(philo);
	log_text(philo, EAT);
	sleep_chunks(philo, philo->data->tte);
	update_num_eat(philo);
	drop_off(philo);
}

void	*routine(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	usleep(500);
	while (!philo->data->end && !philo->if_eat_max)
	{
		eating(philo);
		if (philo->data->end)
			break ;
		if (philo->num_eat == philo->data->must_eat)
			philo->if_eat_max = true;
		else if (!philo->data->end)
			think(philo);
	}
	return (NULL);
}
