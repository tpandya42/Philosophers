#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!content(&data, av + 1, ac - 1))
		return (EXIT_FAILURE);
}
