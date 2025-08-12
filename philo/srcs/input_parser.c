#include "philo.c"

static void	init_inp(t_data *data, long *inp[5])
{
	inp[0] = &data->num_ph;
	inp[1] = &data->ttd;
	inp[2] = &data->tte;
	inp[3] = &data->tts;
	inp[4] = &data->must_eat;
}

static int get_data_0(long *inp, char *av)
{
    int success;

    success = ft_atol(av, inp);
    if (!success || *inp < 1)
    {
        write(2, "Parsing Failed\n", 15);
        return 0;
    }
    return 1;
}


static int	get_data_1(t_data *data, char **av, int ac)
{
	long	*inp[5];
	int	i;

	init_inp(data, inp);
	i = 0;
	while (i < ac)
	{
		if (!get_data_0(inp[i], av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	content(t_data *data, char **av, int ac)
{
	if (ac !=4 && ac != 5)
	{
		write (2, "Invalid number of arguments\n", 28);
		return (0);
	}
	data->must_eat  = -1;
	if (!get_data_1(data, av, ac))
		return (0);
	return (1);
}
