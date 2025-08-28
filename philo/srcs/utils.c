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

void clean_all_0(t_data *data)
{
    int i;

    if (!data)
        return;

    if (data->philo)
    {
        i = 0;
        while (i < data->num_ph)
        {
            pthread_mutex_destroy(&data->philo[i].lock);
            i++;
        }
        free(data->philo);
        data->philo = NULL;
    }

    if (data->stick)
    {
        i = 0;
        while (i < data->num_ph)
        {
            pthread_mutex_destroy(&data->stick[i].stick);
            i++;
        }
        free(data->stick);
        data->stick = NULL;
    }

    pthread_mutex_destroy(&data->death);
    pthread_mutex_destroy(&data->print);
}



int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		i++;
	return (i);
}

long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
}
