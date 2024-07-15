#include "philo.h"


void parse_data(t_data *data, char **av)
{
  for (int i = 1 ; i < 5 ; i++)
  data->philos = atoi(av[1]);
  data->time_to_die = atoi(av[2]);
  data->time_to_eat = atoi(av[3]);
  data->time_to_sleep = atoi(av[4]);
  data->ph_th = (pthread_t *) malloc(sizeof(pthread_t) * data->philos);
}

int getCurrentTime(struct timeval *currentTime)
{
  struct timeval elapsedTime;
  gettimeofday(&elapsedTime, NULL);
  return ((elapsedTime.tv_sec * 1000 + elapsedTime.tv_usec / 1000) - ((currentTime->tv_sec) * 1000 + (currentTime->tv_usec) / 1000));
}
void *routine(void *v_data)
{
  // each fork protected 
//time_to_die (in milliseconds): 
//If a philosopher didn’t start eating time_to_die
//milliseconds since the beginning of their last meal
//or the beginning of the simulation, they die.
  t_data *data = (t_data *)v_data;
  pthread_mutex_lock(&(data->i_mutex));
  int index =  data->philo_id--;
  printf("index is %d\n", index);
  pthread_mutex_unlock(&(data->i_mutex));
  pthread_cond_signal(&(data->iCond));
  while (1)
  {
  pthread_mutex_lock (&(data->forkMutex));
  // get currenttime; , pthread_self()
  printf("%d ms philosopher number %d has taken a fork\n",
      getCurrentTime(&(data->currentTime)), index);
  sleep(1); 
  printf("%d ms philosopher number %d is eating id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self());
  sleep(1);
  printf("%d ms philosopher number %d is sleeping id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self());
  sleep(1);
  printf("%d ms philosopher number %d is thinking id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self()); 
  sleep(1);
  printf("%d ms philosopher number %d died id : %lu\n",getCurrentTime(&(data->currentTime)), index , pthread_self());
  sleep(1);
  // all data should be in a mutex;
  pthread_mutex_unlock (&(data->forkMutex));
  usleep(500);
  }
  return (NULL);
}

int main(int ac, char **av)
{
  if (ac < 5)
    return (0);
  t_data *data = malloc(sizeof(t_data));
  parse_data(data, av);
  gettimeofday(&(data->currentTime), NULL); // ? 
  //data->start_time = data->currentTime.tv_usec; // ? 
  pthread_mutex_init(&(data->forkMutex), NULL); 
  pthread_mutex_init(&(data->i_mutex), NULL);
  pthread_cond_init(&(data->iCond), NULL);
  for (int i = 0 ; i < data->philos ; i++)
  {
    pthread_mutex_lock(&(data->i_mutex));
    data->philo_id = i;
    // wait for a signal that a thread received this varaible
    pthread_create(data->ph_th + i, NULL, &routine, (void *)data);
    while (i == data->philo_id) /* make sure there is a thread*/
    {
      printf("73 loop\n");
      pthread_cond_wait(&(data->iCond), &(data->i_mutex));
    }
    pthread_mutex_unlock(&(data->i_mutex));
  }
  for (int i = 0 ; i < data->philos ; i++)
    pthread_join(data->ph_th[i], NULL);
  pthread_mutex_destroy(&(data->forkMutex));
  pthread_mutex_destroy(&(data->i_mutex));
  pthread_cond_destroy(&(data->iCond));
  return (0);
}
