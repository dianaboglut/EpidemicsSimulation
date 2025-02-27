#ifndef PERS_H
#define PERS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define INFECTED_DURATION 2
#define IMMUNE_DURATION 5
#define INFECTED 0
#define SUSCEPTIBLE 1
#define IMMUNE 2

typedef struct{
    int personID;
    int x,y;    // Coordinates
    int status; // 0 = infected, 1 = susceptible, 2 = immune
    int futureStatus; // 0 = infected, 1 = susceptible, 2 = immune
    int direction;  // Movement Direction: N=0, S=1, E=2, W=3
    int amplitude; // How far away is one movement
    int infectionCounter; // Counting the number of times a person got infected
    int infectedTime;  //keeps track of how long the person has been infected
    int immuneTime; // keeps track of how long the person has been immune
}Person;

void updatePositionOfAPerson(Person *p,int max_X,int max_Y);
void updateFutureStatus(Person *p1);
void updateInfectionStatus(Person *p1);

#endif
