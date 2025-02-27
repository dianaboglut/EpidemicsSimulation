#include "include.h"

int **infectedPersons;

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("Usage: %s <TOTAL_SIMULATION_TIME> <InputFileName> <ThreadNumber>\n", argv[0]);
        return 1;
    }

    totalSimulationTime = atoi(argv[1]);
    char *fileName = argv[2];
    threadCount = atoi(argv[3]);

//---------------------------------- Serial ---------------------------------------------
        //  Reding data from file and initializing the arrat of persons
    readInput(fileName);

    #ifdef DEBUG
        printf("\n\tSTART SIMULATION\n\n");
    #endif

    // Init stuff
    infectedPersons=malloc(max_y_coord * sizeof(int*));
    for(int i=0; i < max_y_coord; i++){
        infectedPersons[i] = calloc(max_x_coord, sizeof(int));
    }

        // Measuring Performance for Serial Simulation
    struct timespec start, finish;
    double elapsed_serial, elapsed_parallel;
    printf("\t___SERIAL___: \n");
    clock_gettime(CLOCK_MONOTONIC, &start); // measure wall clock time!

    runSimulation();

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed_serial = (finish.tv_sec - start.tv_sec);
    elapsed_serial += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time =%lf \n", elapsed_serial);
            // Writing the serial output of simulation in the file
    writeFileSerial(fileName,totalSimulationTime);

        //  Copying the persons array to use it later for checking equality
    Person *serialPerson = malloc(numberPersons * sizeof(Person));
    if(serialPerson == NULL){
        perror("Could not create memory for serialPerson");
        exit(-1);
    }
        //memcpy is used to copy a block of memory from one location to another. It’s particularly useful when you need to move a large amount of data efficiently, especially in low-level operations or within data structures where direct memory access is needed.
    memcpy(serialPerson,persons,numberPersons * sizeof(Person));

//---------------------------------- Parallel ---------------------------------------------
        //  Reading again the file for parallel computation
    readInput(fileName);
    
    // Reset infectedPersons for parallel Computation
    for(int i=0; i < max_y_coord; i++){
        for(int j=0; j < max_x_coord; j++){
            infectedPersons[i][j] = 0;
        }
    }

    printf("\t___PARALLEL___: \n");
    clock_gettime(CLOCK_MONOTONIC, &start); // measure wall clock time!

    runSimulationParallel();

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed_parallel = (finish.tv_sec - start.tv_sec);
    elapsed_parallel += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time =%lf \n", elapsed_parallel);
        // Writing the parallel output of simulation in the file
    writeFileParallel(fileName,totalSimulationTime);

        // Comapring serial results with parallel results 
    if (!Equal_data(serialPerson,persons))
      printf("Error! Serial and Parallel results not equal! \n");

   printf("Number of parallel threads was %d\n", threadCount);
   printf("Measured Speedup= %f\n ", elapsed_serial / elapsed_parallel);

        //  Free memory
    for (int i = 0; i < max_x_coord; i++) {
        free(infectedPersons[i]);
    }
    free(infectedPersons);
    free_simulation();
    return 0;
}