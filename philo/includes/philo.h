#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data t_data;

// CHOPSTICK - > instead of forks (use chopsticks >>) just a array of mutexes nothing deep;
typedef struct s_chopstick
{
	pthread_mutex_t	stick;
	int				stick_id;
}					t_chopstick;

// PHILOOO - > to hold info for each philo
typedef struct s_ph
{
	pthread_t			thread_id;
	int				id;
	int				num_eat;
	long			last_time_eat;
	bool			if_eat_max;
	t_chopstick		*left_stick;
	t_chopstick		*right_stick;
	t_data			*data;

}					t_ph;

// DATA - > input data + other useful data
struct s_data
{
	long				num_ph;
	long				ttd;
	long				tte;
	long				tts;
	long				must_eat;
	long			start_time;
	bool			end;
	t_chopstick		*stick;
	t_ph			*philo;
};

// TASKS -> just for better readability.
typedef enum e_tasks
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}					t_tasks;

typedef enum e_status
{
	SUCCESS,
	FAILURE
}					t_status;

long	ft_atol(const char *str);
int	ft_strlen(char *str);
char				*ft_strcpy(char *dest, const char *src);
int	content(t_data *data, char **av, int ac);
int	init_init(t_data *data, char **av, int ac);
int	run(t_data *data);
void	*routine(void *arg);
void	clean_all_0(t_data *data);
long	get_time_in_ms(void);
void	error_exit(const char *error);
#endif
