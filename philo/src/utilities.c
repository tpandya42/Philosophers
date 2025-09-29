#include "dining_philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	log_philosopher_action(t_thinker *philosopher, t_action action)
{
	long		timestamp;
	const char	*action_str;

	if (action == TAKE_UTENSIL)
		action_str = "has taken a fork";
	else if (action == CONSUME_FOOD)
		action_str = "is eating";
	else if (action == REST)
		action_str = "is sleeping";
	else if (action == CONTEMPLATE)
		action_str = "is thinking";
	else if (action == PERISH)
		action_str = "died";
	else
		return ;
	pthread_mutex_lock(&philosopher->sim->output_mutex);
	if (!check_simulation_end(philosopher->sim) || action == PERISH)
	{
		timestamp = get_current_time_ms() - philosopher->sim->simulation_start;
		printf("%ld %d %s\n", timestamp, philosopher->number, action_str);
	}
	pthread_mutex_unlock(&philosopher->sim->output_mutex);
}

int	parse_positive_int(const char *str)
{
	long	result;
	int		i;

	if (!str || !str[0])
		return (-1);
	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (-1);
	return ((int)result);
}

void	precise_sleep(int duration_ms)
{
	usleep(duration_ms * 1000);
}
