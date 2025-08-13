#include "philo.h"

static int parse_arg(const char *str, long *dest, char *err_msg)
{
	long tmp;

	tmp = ft_atol(str); // will exit on error
	if (tmp < 1)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		return FAILURE;
	}
	*dest = tmp;
	return SUCCESS;
}

int content(t_data *data, char **av, int ac)
{
	if (ac != 5 && ac != 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return FAILURE;
	}

	if (parse_arg(av[1], &data->num_ph, "Invalid number_of_philosophers") ||
			parse_arg(av[2], &data->ttd,    "Invalid time_to_die") ||
			parse_arg(av[3], &data->tte,    "Invalid time_to_eat") ||
			parse_arg(av[4], &data->tts,    "Invalid time_to_sleep"))
		return FAILURE;

	if (ac == 6)
	{
		if (parse_arg(av[5], &data->must_eat, "Invalid must_eat value"))
			return FAILURE;
	}
	else
		data->must_eat = -1;
	printf("success from content\n");
	return SUCCESS;
}

