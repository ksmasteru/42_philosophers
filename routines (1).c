#include "philo.h"

int philo_take_fork(t_data *data, int index)
{
    printf("%d ms philosopher number %d has taken a fork\n", 
        getCurrentTime(&(data->currentTime)), index);
    return (0);
}
int philo_eat(t_data *data, int index)
{
    gettimeofday(&(data->hungry_time[index]), NULL);/* time reset*/
    printf("%d ms philosopher number %d is eating id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self());
    usleep(data->time_to_eat * 1000);    
    return (0);
}

int philo_think(t_data *data, int index)
{
    printf("%d ms philosopher number %d is thinking id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self());
    //thinks until he gets a fork. condvariable;
    // wait for a signal == cond_variable
    return (0);
}

int philo_sleep(t_data *data, int index)
{
    printf("%d ms philosopher number %d is sleeping id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self());
    usleep(data->time_to_sleep * 1000);
    return (0);
}

