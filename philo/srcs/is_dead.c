#include "philo.h"

void	*checker(void *arg)
{
	t_data *data = (t_data *)arg;
	int	i;
	long	time_since_last_meal;
	int	all_done;

	time_since_last_meal = 0;
	while (1)
	{
		i = 0;
		all_done = 1;
		while (i < data->num_ph)
		{
			pthread_mutex_lock(&data->philo[i].lock); // protect last_eaten
			time_since_last_meal = get_time_in_ms() - data->philo[i].last_eaten;
			pthread_mutex_unlock(&data->philo[i].lock);

			if (time_since_last_meal >= data->ttd)
			{
				pthread_mutex_lock(&data->death);       // ensure only one death happens
				if (!data->end)
				{
					data->end = true;

					pthread_mutex_lock(&data->write);   // protect log output
					log_text(&data->philo[i], DIE);
					pthread_mutex_unlock(&data->write);
				}
				pthread_mutex_unlock(&data->death);
				pthread_mutex_unlock(&data->philo[i].lock);
				return NULL; // exit checker thread
			}
			if (data->philo[i].num_eat < data->must_eat)
				all_done = 0;
			pthread_mutex_unlock(&data->philo[i].lock);
			i++;
		}
		if (all_done)
		{
			pthread_mutex_lock(&data->death);
			data->end = true;
			pthread_mutex_unlock(&data->death);
			return NULL;
		}
		usleep(1000); // avoid busy loop
	}
	return NULL;
}

