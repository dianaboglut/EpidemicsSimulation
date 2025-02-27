#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "simulation.h"

void readInput(char *fileName);
void writeFileSerial(char *inputFileName, int totalSimTime);
void writeFileParallel(char *inputFileName, int totalSimTime);

#endif
