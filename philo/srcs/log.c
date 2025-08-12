#include "philo.h"


static void	text(char *log, t_tasks task)
{
	if (task == DIE)
		ft_strcpy(log, "died");
	else if (task = FORK)
		ft_strcpy(log, "has taken a fork");
	else if (task = EAT)
		ft_strcpy(log, "is eating");
	else if (task = SLEEP)
		ft_strcpy(log, "is sleeping");
	else if (task = THINK)
		ft_strcpy(log, "is thinking");
}

void	log(t_task task, t_ph *ph)
{
	char	*log;

	text(log, last);
}
