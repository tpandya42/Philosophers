/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:26:36 by tpandya           #+#    #+#             */
/*   Updated: 2025/09/19 11:26:38 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_chopstick
{
	pthread_mutex_t		stick;
	int					stick_id;
}						t_chopstick;

typedef struct s_ph
{
	pthread_t			thread_id;
	int					id;
	int					num_eat;
	bool				if_eat_max;
	long				last_eaten;

	t_chopstick			*left_stick;
	t_chopstick			*right_stick;
	t_data				*data;
	pthread_mutex_t		lock;
}						t_ph;

// DATA - > input data + other useful data
struct					s_data
{
	long				num_ph;
	long				ttd;
	long				tte;
	long				tts;
	long				must_eat;
	long				start_time;
	bool				end;
	pthread_mutex_t		death;
	pthread_mutex_t		print;
	t_chopstick			*stick;
	t_ph				*philo;
};

typedef enum e_tasks
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}						t_tasks;

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum e_status
{
	SUCCESS,
	FAILURE
}						t_status;

long					ft_atol(const char *str);
int						ft_strlen(char *str);
char					*ft_strcpy(char *dest, const char *src);
int						content(t_data *data, char **av, int ac);
int						init_init(t_data *data, char **av, int ac);
int						run(t_data *data);
void					pick_up(t_ph *philo);
void					sleep_chunks(t_ph *philo, int time);
void					drop_off(t_ph *philo);
void					think(t_ph *philo);
void					log_text(t_ph *philo, t_tasks task);
void					*routine(void *arg);
void					clean_all_0(t_data *data);
long					get_time_in_ms(void);
void					error_exit(const char *error);
void					*checker(void *arg);

#endif
