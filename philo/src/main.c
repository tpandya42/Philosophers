#include "dining_philosophers.h"

static int	handle_single_philosopher(t_simulation *sim)
{
	sim->simulation_start = get_current_time_ms();
	printf("%ld 1 has taken a fork\n", 0L);
	usleep(sim->death_timer * 1000); // Convert milliseconds to microseconds
	printf("%ld 1 died\n", (long)sim->death_timer);
	return (0);
}

static int	validate_and_parse_args(int argc, char **argv, t_simulation *sim)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <philosophers> <die_time> <eat_time> <sleep_time> [must_eat]\n", argv[0]);
		return (1);
	}
	
	sim->thinker_count = parse_positive_int(argv[1]);
	sim->death_timer = parse_positive_int(argv[2]);
	sim->eating_duration = parse_positive_int(argv[3]);
	sim->sleeping_duration = parse_positive_int(argv[4]);
	
	if (sim->thinker_count <= 0 || sim->death_timer <= 0 || 
		sim->eating_duration <= 0 || sim->sleeping_duration <= 0)
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	
	if (sim->thinker_count > MAX_PHILOSOPHERS)
	{
		printf("Error: Too many philosophers (max %d)\n", MAX_PHILOSOPHERS);
		return (1);
	}
	
	if (argc == 6)
	{
		sim->required_bites = parse_positive_int(argv[5]);
		if (sim->required_bites <= 0)
		{
			printf("Error: Required meals must be positive\n");
			return (1);
		}
	}
	else
		sim->required_bites = -1;
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	printf("DEBUG: Starting main with %d arguments\n", argc);
	if (validate_and_parse_args(argc, argv, &sim))
		return (1);
	
	printf("DEBUG: Parsed args - philosophers: %d, death_timer: %d\n", sim.thinker_count, sim.death_timer);
	
	if (sim.thinker_count == 1)
	{
		printf("DEBUG: Handling single philosopher\n");
		return (handle_single_philosopher(&sim));
	}
	
	printf("DEBUG: Initializing simulation\n");
	if (initialize_simulation(&sim, argc, argv))
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	
	printf("DEBUG: Launching simulation\n");
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