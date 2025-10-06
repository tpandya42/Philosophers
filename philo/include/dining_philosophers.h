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
	int				philo_id;
	long				last_eatten;
	int				times_eaten;
	bool				finished_eating;
	t_simulation		*sim;
	pthread_t			life_thread;
	pthread_mutex_t	eat_time_mutex;
	pthread_mutex_t	eat_count_mutex;
};

// Main simulation data
struct s_simulation
{
	int				no_philo;
	int				death_timer;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	long				simulation_start;
	bool				simulation_over;
	pthread_t			monitor_thread;
	pthread_t			completion_thread;
	t_thinker			*philos;
	pthread_mutex_t	end_simulation_mutex;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	*sticks;
};

// Action types for logging
typedef enum e_action
{
	STICK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_action;

// Core simulation functions
int		initialize_simulation(t_simulation *sim, int argc, char **argv);
int		launch_simulation(t_simulation *sim);
int		terminate_simulation(t_simulation *sim);
void	cleanup_simulation(t_simulation *sim);

// Philosopher lifecycle
void	*routine(void *philosopher);
void	take_sticks(t_thinker *philosopher);
void	drop(t_thinker *philosopher);
void	eatting(t_thinker *philosopher);
void	take_rest(t_thinker *philosopher);
void	thinking(t_thinker *philosopher);

// Monitoring functions
void	*death_checker(void *simulation);
void	*completion_watch(void *simulation);
bool	check_simulation_end(t_simulation *sim);
void	end_simulation(t_simulation *sim);

// Synchronization helpers
long	eat_time(t_thinker *philosopher);
void	update_time(t_thinker *philosopher);
int		get_bite_count(t_thinker *philosopher);
void	increment_bites(t_thinker *philosopher);

// Utility functions
long	get_current_time_ms(void);
void	philosopher_log(t_thinker *philosopher, t_action action);
#define log philosopher_log
int	parse(const char *str);
unsigned int	sleep(unsigned int duration_ms);

#endif
