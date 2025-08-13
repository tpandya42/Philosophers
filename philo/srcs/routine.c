#include "philo.h"

void *routine(void *arg)
{
    t_ph *philo = (t_ph *)arg;

    printf("Philosopher %d started!\n", philo->id);
    fflush(stdout);          
    usleep(500000);          
    printf("Philosopher %d finished!\n", philo->id);
    fflush(stdout);

    return NULL;
}
