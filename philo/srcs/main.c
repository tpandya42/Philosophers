#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_ph	*philo;
	t_chopstick	*stick;

	if (init_init(data, av, ac) == FAILURE){
		clean_all_0(data);
		return (EXIT_FAILURE);
	}
}
