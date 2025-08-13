#include "philo.h"

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
        return FAILURE;
    }
    printf("inp: %ld", *inp);
    return SUCCESS;
}


static int	get_data_1(t_data *data, char **av, int ac)
{
	long	*inp[5];
	int	i;

	init_inp(data, inp);
	i = 0;
	while (i < ac)
	{
		if (get_data_0(inp[i], av[i]) == FAILURE)
			return FAILURE;
		i++;
	}
	printf("Got all the inputs\n");
	return (SUCCESS);
}

int	content(t_data *data, char **av, int ac)
{
	if (ac !=4 && ac != 5)
	{
		write (2, "Invalid number of arguments\n", 28);
		return FAILURE;
	}
	data->must_eat  = -1;
	if (get_data_1(data, av, ac) == FAILURE)
		return FAILURE;
	printf("Got the content\n");
	return SUCCESS;
}
