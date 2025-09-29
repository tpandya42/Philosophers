#include "dining_philosophers.h"

long	get_bite_time(t_thinker *philosopher)
{
	long	time;

	pthread_mutex_lock(&philosopher->bite_time_mutex);
	time = philosopher->time_last_bite;
	pthread_mutex_unlock(&philosopher->bite_time_mutex);
	return (time);
}

void	update_bite_time(t_thinker *philosopher)
{
	pthread_mutex_lock(&philosopher->bite_time_mutex);
	philosopher->time_last_bite = get_current_time_ms();
	pthread_mutex_unlock(&philosopher->bite_time_mutex);
}

int	get_bite_count(t_thinker *philosopher)
{
	int	count;

	pthread_mutex_lock(&philosopher->bite_count_mutex);
	count = philosopher->bites_consumed;
	pthread_mutex_unlock(&philosopher->bite_count_mutex);
	return (count);
}

void	increment_bite_count(t_thinker *philosopher)
{
	pthread_mutex_lock(&philosopher->bite_count_mutex);
	philosopher->bites_consumed++;
	pthread_mutex_unlock(&philosopher->bite_count_mutex);
}