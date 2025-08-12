#include "philo.h"


static t_status join_threads(pthread_t *threads, t_data *data)
{
    int i;

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
	return(SUCCESS);
}

int	run(t_data *data)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->num_ph);
	if (!threads)
		return FAILURE;
	if (create_threads(threads, data) == FAILURE)
		return (free(threads), FAILURE);
	if (join_threads(threads, data) == FAILURE)
		return (free(threads), FAILURE);
	free(threads);
}
