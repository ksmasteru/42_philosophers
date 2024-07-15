#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>

typedef struct s_data{
  int philos;
  int time_to_die;
  int time_to_eat;
  int philo_id;
  int time_to_sleep;
  struct timeval currentTime;
  pthread_t *ph_th;
  pthread_mutex_t forkMutex;
  pthread_mutex_t i_mutex;
  pthread_cond_t iCond;
}t_data;
#endif
