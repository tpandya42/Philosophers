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

#include "dining_philosophers.h"

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

int	parse(const char *str)
{
	long	result;
	int		i;

	if (!str || !str[0])
		return (-1);
	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (-1);
	return ((int)result);
}

unsigned int	sleep(unsigned int duration_ms)
{
	usleep(duration_ms * 1000);
	return (0);
}
