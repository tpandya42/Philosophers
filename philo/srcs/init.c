#include "philo.h"

static int	init_struct_data(t_data *data)
{
	data->num_ph = 0;
	data->ttd = 0;
	data->tte = 0;
	data->tts = 0;
	data->must_eat = 0;
	data->start_time = 0;

	return (1);
}

static int	init_chopsticks(t_data *data)
{
	int	i;

	data->stick = malloc(sizeof(t_chopstick) * data->num_ph);
	if (!data->stick)
		return (FAILURE);
	i = 0;
	while (i < data->num_ph)
	{
		data->stick[i].stick_id = i;
		if (pthread_mutex_init(&data->stick[i].stick, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	init_struct_philo(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_ph) * data->num_ph);
	if (!data->philo)
		return (FAILURE);
	i = 0;
	while (i < data->num_ph)
	{
		data->philo[i].id = i + 1;
		data->philo[i].num_eat = 0;
		data->philo[i].last_time_eat = 0;
		data->philo[i].if_eat_max = false;
		data->philo[i].left_stick = &data->stick[i];
		data->philo[i].right_stick = &data->stick[(i + 1) % data->num_ph];
		data->philo[i].data = data;
		i++;
	}
	return (SUCCESS);
}

int	init_init(t_data *data, char **av, int ac)
{
	if (!init_struct_data(data))
		return (FAILURE);
	if (!content(data, av + 1, ac - 1))
		return (FAILURE);
	if (data->num_ph <= 0 || data->ttd <= 0 || data->tte <= 0 || data->tts <= 0 || (ac == 5 && data->must_eat <= 0))
		return (FAILURE);
	if (!init_chopsticks(data))
		return (FAILURE);
	return (init_struct_philo(data));
}
