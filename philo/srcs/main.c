#include "philo.h"

int main(int ac, char **av)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data)
        return EXIT_FAILURE;

    if (init_init(data, av, ac) == FAILURE || run(data) == FAILURE)
    {
        clean_all_0(data);
        free(data);
        return EXIT_FAILURE;
    }

    clean_all_0(data);
    free(data);
    return EXIT_SUCCESS;
}

