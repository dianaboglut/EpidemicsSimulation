#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "person.h"

extern int max_x_coord;
extern int max_y_coord;
extern Person *persons;    // Array of persons
extern int numberPersons;

extern int threadCount;
extern int totalSimulationTime;

extern int **infectedPersons;

// The barrier for sync
extern pthread_barrier_t mybarrier;
extern pthread_mutex_t infectedPersons_mutex;

void runSimulation();
void *runSimParallel(void *rank);
void runSimulationParallel();
void free_simulation();

int Equal_data(Person *serialPersons, Person *parallelPersons);

#endif
