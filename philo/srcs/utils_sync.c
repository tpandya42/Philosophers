/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:00:00 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/28 17:00:01 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_ended(t_ph *philo)
{
	int	ended;
	
	pthread_mutex_lock(&philo->data->death);
	ended = philo->data->end;
	pthread_mutex_unlock(&philo->data->death);
	return (ended);
}