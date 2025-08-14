#include "philo.h"

// Fill a buffer safely
static void text(char *log, t_tasks task)
{
    if (!log)
        return;

    if (task == DIE)
        ft_strcpy(log, "died");
    else if (task == FORK)
        ft_strcpy(log, "has taken a fork");
    else if (task == EAT)
        ft_strcpy(log, "is eating");
    else if (task == SLEEP)
        ft_strcpy(log, "is sleeping");
    else if (task == THINK)
        ft_strcpy(log, "is thinking");
}

void log_text(t_ph *philo, t_tasks task)
{
    static const size_t MAX_LOG_LEN = 32;
    char buffer[MAX_LOG_LEN];

    text(buffer, task);

    long timestamp = get_time_in_ms() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print);
    printf("%ld: Philosopher %d %s\n", timestamp, philo->id, buffer);
    pthread_mutex_unlock(&philo->data->print);
}

