/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:49:10 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/06 14:49:12 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dining_philosophers.h"

long	eat_time(t_thinker *philosopher)
{
	long	time;

	pthread_mutex_lock(&philosopher->eat_time_mutex);
	time = philosopher->last_eatten;
	pthread_mutex_unlock(&philosopher->eat_time_mutex);
	return (time);
}

void	update_time(t_thinker *philosopher)
{
	pthread_mutex_lock(&philosopher->eat_time_mutex);
	philosopher->last_eatten = get_current_time_ms();
	pthread_mutex_unlock(&philosopher->eat_time_mutex);
}

int	get_eat_count(t_thinker *philosopher)
{
	int	count;

	pthread_mutex_lock(&philosopher->eat_count_mutex);
	count = philosopher->times_eaten;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
	return (count);
}

void	increment_bites(t_thinker *philosopher)
{
	pthread_mutex_lock(&philosopher->eat_count_mutex);
	philosopher->times_eaten++;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
}
