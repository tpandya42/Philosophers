/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:28:26 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:28:27 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	text(char *log, t_tasks task)
{
	if (!log)
		return ;
	if (task == DIE)
		ft_strcpy(log, "died");
	else if (task == FORK)
		ft_strcpy(log, "has taken a fork");
	else if (task == EAT)
		ft_strcpy(log, "is eating");
	else if (task == SLEEP)
		ft_strcpy(log, "is sleeping");
	else if (task == THINK)
		ft_strcpy(log, "is thinking");
}

void	log_text(t_ph *philo, t_tasks task)
{
	char				buffer[32];
	long				timestamp;

	if (philo->data->end && task != DIE)
		return ;
	text(buffer, task);
	timestamp = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->end || task == DIE)
		printf("%ld %d %s\n", timestamp, philo->id, buffer);
	pthread_mutex_unlock(&philo->data->print);
}
