/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:30:07 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:30:09 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	destroy_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_ph)
	{
		pthread_mutex_destroy(&data->philo[i].lock);
		i++;
	}
	free(data->philo);
	data->philo = NULL;
}

static void	destroy_sticks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_ph)
	{
		pthread_mutex_destroy(&data->stick[i].stick);
		i++;
	}
	free(data->stick);
	data->stick = NULL;
}

void	clean_all_0(t_data *data)
{
	if (!data)
		return ;
	if (data->philo)
		destroy_philos(data);
	if (data->stick)
		destroy_sticks(data);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
}
