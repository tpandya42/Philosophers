#include "philo.h"

int main(int ac, char **av)
{
	t_data *data = malloc(sizeof(t_data));
	if (!data)
		return EXIT_FAILURE;

	if (init_init(data, av, ac) == FAILURE)
	{
		clean_all_0(data);
		free(data);
		return EXIT_FAILURE;
	}

	// Initialize simulation start time here
	data->start_time = get_time_in_ms();
	if (run(data) == FAILURE)
	{
		clean_all_0(data);
		free(data);
		return EXIT_FAILURE;
	}
	printf("%ld: \n", data->start_time);
	clean_all_0(data);
	free(data);
	return EXIT_SUCCESS;
}


