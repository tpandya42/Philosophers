#include "philo.h"

void pick_up(t_ph *philo)
{
    	pthread_mutex_lock(&philo->left_stick->stick);
	log_text(philo, FORK);
	pthread_mutex_lock(&philo->right_stick->stick);
	log_text(philo, FORK);
}

void	drop_off(t_ph *philo)
{
	pthread_mutex_unlock(&philo->left_stick->stick);
	pthread_mutex_unlock(&philo->right_stick->stick);
	log_text(philo, SLEEP);
	usleep(philo->data->tts);
}

void	eating(t_ph *philo)
{
	pick_up(philo);
	pthread_mutex_lock(&philo->lock);
	log_text(philo, EAT);
	usleep(philo->data->tte);
	philo->num_eat++;
	pthread_mutex_unlock(&philo->lock);
	drop_off(philo);
}

void *routine(void *arg)
{
    t_ph *philo = (t_ph *)arg;

    usleep(500);

    while (!philo->data->end && !philo->if_eat_max)
    { 
	eating(philo);
        if (philo->num_eat == philo->data->must_eat)
            philo->if_eat_max = true;
	
	log_text(philo, THINK);
    }
    return NULL;
}

