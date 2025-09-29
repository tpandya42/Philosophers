#ifndef DINING_PHILOSOPHERS_H
# define DINING_PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# define MAX_PHILOSOPHERS 200
# define MICRO_TO_MILLI 1000

// Forward declarations
typedef struct s_simulation	t_simulation;
typedef struct s_thinker	t_thinker;

// Individual philosopher structure
struct s_thinker
{
	int					number;
	long				time_last_bite;
	int					bites_consumed;
	bool				finished_eating;
	t_simulation		*sim;
	pthread_t			life_thread;
	pthread_mutex_t		bite_time_mutex;
	pthread_mutex_t		bite_count_mutex;
};

// Main simulation data
struct s_simulation
{
	int					thinker_count;
	int					death_timer;
	int					eating_duration;
	int					sleeping_duration;
	int					required_bites;
	long				simulation_start;
	bool				simulation_over;
	pthread_t			supervisor_thread;
	pthread_t			completion_thread;
	t_thinker			*thinkers;
	pthread_mutex_t		end_simulation_mutex;
	pthread_mutex_t		output_mutex;
	pthread_mutex_t		*utensils;
};

// Action types for logging
typedef enum e_action
{
	TAKE_UTENSIL,
	CONSUME_FOOD,
	REST,
	CONTEMPLATE,
	PERISH
}	t_action;

// Core simulation functions
int		initialize_simulation(t_simulation *sim, int argc, char **argv);
int		launch_simulation(t_simulation *sim);
int		terminate_simulation(t_simulation *sim);
void	cleanup_simulation(t_simulation *sim);

// Philosopher lifecycle
void	*philosopher_routine(void *philosopher);
void	acquire_utensils(t_thinker *philosopher);
void	release_utensils(t_thinker *philosopher);
void	consume_meal(t_thinker *philosopher);
void	take_rest(t_thinker *philosopher);
void	think_deeply(t_thinker *philosopher);

// Monitoring functions
void	*supervise_deaths(void *simulation);
void	*monitor_completion(void *simulation);
bool	check_simulation_end(t_simulation *sim);
void	end_simulation(t_simulation *sim);

// Synchronization helpers
long	get_bite_time(t_thinker *philosopher);
void	update_bite_time(t_thinker *philosopher);
int		get_bite_count(t_thinker *philosopher);
void	increment_bite_count(t_thinker *philosopher);

// Utility functions
long	get_current_time_ms(void);
void	log_philosopher_action(t_thinker *philosopher, t_action action);
int		parse_positive_int(const char *str);
void	precise_sleep(int duration_ms);

#endif