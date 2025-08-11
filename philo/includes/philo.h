#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_data {
	int	num_ph;
	int	ttd;
	int	tte;
	int	tts;
	int	must_eat;
}		t_data;

typedef struct s_ph{
	pthread_t	thread;
	int		id;
	int		num_eat;
	int		last_time_eat;
	t_data		*data;

}	t_ph;

typedef enum e_tasks
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_tasks;

int	ft_atoi(const char *str, int *res);
char	*ft_strcpy(char *dest, const char *src);

#endif
