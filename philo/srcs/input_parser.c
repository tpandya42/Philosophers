#include "philo.h"

static int parse_number(const char *str, long *dest, int convert, char *err_msg)
{
    long tmp;

    tmp = ft_atol(str); 
    if (tmp < 1)
    {
        write(2, err_msg, ft_strlen(err_msg));
        write(2, "\n", 1);
        return FAILURE;
    }

    *dest = tmp * convert; 
    return SUCCESS;
}

int content(t_data *data, char **av, int ac)
{
	if (ac != 5 && ac != 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return FAILURE;
	}
	if (parse_number(av[1], &data->num_ph, 1, "Invalid number_of_philosophers") ||
			parse_number(av[2], &data->ttd,    1, "Invalid time_to_die") ||
			parse_number(av[3], &data->tte,    1, "Invalid time_to_eat") ||
			parse_number(av[4], &data->tts,    1, "Invalid time_to_sleep"))
		return FAILURE;

	if (ac == 6)
	{
		if (parse_number(av[5], &data->must_eat, 1, "Invalid must_eat value"))
			return FAILURE;
	}
	else
		data->must_eat = -1;
	printf("Arguments parsed successfully!\n");
	return SUCCESS;
}

