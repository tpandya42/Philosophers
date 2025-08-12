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

void	clean_all_0(t_data *data)
{
	int	i;

	if (data == NULL)
		return ;
	if (data->philo != NULL)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->stick != NULL)
	{
		i = 0;
		while (i < data->num_ph)
			pthread_mutex_destroy(&data->stick[i++].stick);
		free(data->stick);
		data->stick = NULL;

	}
}
