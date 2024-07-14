#include "philo.h"


void parse_data(t_data *data, char **av)
{
  for (int i = 1 ; i < 5 ; i++)
    printf("av[%d] is %s\n", i, av[i]);
  data->philos = atoi(av[1]);
  printf("philos number is %d\n", data->philos);
  data->time_to_die = atoi(av[2]);
  printf("time to die is %d\n", data->time_to_die);
  data->time_to_eat = atoi(av[3]);
  printf("time to eat is %d\n", data->time_to_eat);
  data->time_to_sleep = atoi(av[4]);
  printf("time to sleep is %d\n", data->time_to_sleep);
  //data->ph_th = (pthread_t *) malloc(sizeof(pthread_t) * data->philos);
}

int getCurrentTime(struct timeval *currentTime)
{
  struct timeval elapsedTime;
  gettimeofday(&elapsedTime, NULL);
  return (elapsedTime.tv_usec - currentTime->tv_usec);
}
void *routine(void *v_data)
{
  // each fork protected 
  /*
  * timestamp_in_ms X has taken a fork
◦ * timestamp_in_ms X is eating
◦ * timestamp_in_ms X is sleeping
◦ * timestamp_in_ms X is thinking
◦ * timestamp_in_ms X died */
  t_data *data = (t_data *)v_data;
  pthread_mutex_lock (&(data->forkMutex));
  // get currenttime;
  printf("%d ms philosopher number %d has taken a fork\n",
      getCurrentTime(&(data->currentTime)), *(data->philo_id));
  sleep(3); 
  printf("%d ms philosopher number %d is eating\n",getCurrentTime(&(data->currentTime)), *(data->philo_id));
  sleep(3);
  printf("%d ms philosopher number %d is sleeping\n",getCurrentTime(&(data->currentTime)), *(data->philo_id));
  sleep(3);
  printf("%d ms philosopher number %d is thinking\n",getCurrentTime(&(data->currentTime)), *(data->philo_id)); 
  sleep(3);
  printf("%d ms philosopher number %d died\n",getCurrentTime(&(data->currentTime)), *(data->philo_id));
  sleep(3);
  // all data should be in a mutex;
  free(data->philo_id);
  pthread_mutex_unlock (&(data->forkMutex));
  return (NULL);
}

int main(int ac, char **av)
{
  if (ac < 5)
    return (0);
  t_data *data = malloc(sizeof(data));
  parse_data(data, av);
  gettimeofday(&(data->currentTime), NULL); // ? 
  //data->start_time = data->currentTime.tv_usec; // ? 
  pthread_mutex_init(&(data->forkMutex), NULL); 
  for (int i = 0 ; i < data->philos ; i++)
  {
    data->philo_id = (int *)malloc(sizeof(int));
    *(data->philo_id) = i;
    pthread_create(data->ph_th + i, NULL, &routine, (void *)data);
  }
  for (int i = 0 ; i < data->philos ; i++)
    pthread_join(data->ph_th[i], NULL);
  pthread_mutex_destroy(&(data->forkMutex));
  return (0);
}
