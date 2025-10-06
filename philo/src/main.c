#include "dining_philosophers.h"

static int	handle_single_philosopher(t_simulation *sim)
{
	sim->simulation_start = get_current_time_ms();
	printf("%ld 1 has taken a stick\n", 0L);
	usleep(sim->death_timer * 1000);
	printf("%ld 1 died\n", (long)sim->death_timer);
	return (0);
}

static int	validate_and_parse_args(int argc, char **argv, t_simulation *sim)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n\t%s <philosophers> <die_time> <eat_time> <sleep_time> [must_eat]\n",
			argv[0]);
		return (1);
	}
	sim->no_philo = parse(argv[1]);
	sim->death_timer = parse(argv[2]);
	sim->time_to_eat = parse(argv[3]);
	sim->time_to_sleep = parse(argv[4]);
	if (sim->no_philo <= 0 || sim->death_timer <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	if (sim->no_philo > MAX_PHILOSOPHERS)
	{
		printf("Error: Too many philosophers (max %d)\n", MAX_PHILOSOPHERS);
		return (1);
	}
	if (argc == 6)
	{
		sim->max_eat_count = parse(argv[5]);
		if (sim->max_eat_count <= 0)
		{
			printf("Error: Required meals must be positive\n");
			return (1);
		}
	}
	else
		sim->max_eat_count = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	printf("DEBUG: Starting main with %d arguments\n", argc);
	if (validate_and_parse_args(argc, argv, &sim))
		return (1);
	if (sim.no_philo == 1)
		return (handle_single_philosopher(&sim));
	if (initialize_simulation(&sim, argc, argv))
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	if (launch_simulation(&sim))
	{
		printf("Error: Simulation failed\n");
		cleanup_simulation(&sim);
		return (1);
	}
	printf("DEBUG: Terminating simulation\n");
	if (terminate_simulation(&sim))
	{
		printf("Error: Failed to terminate simulation cleanly\n");
		cleanup_simulation(&sim);
		return (1);
	}
	cleanup_simulation(&sim);
	return (0);
}
