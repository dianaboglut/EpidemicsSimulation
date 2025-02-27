#include "simulation.h"
#include "include.h"

int max_x_coord;
int max_y_coord;
Person *persons;
int numberPersons;

int threadCount;
int totalSimulationTime;

// Auxiliar matrix storing the infected persons so I can easily identify their position 
extern int **infectedPersons;

// Parallel useful thing
pthread_barrier_t mybarrier;
pthread_mutex_t infectedPersons_mutex;

//------------------------------------------------------------------------------------------------------------
//-------------------------------------------- SERIAL SIMULATION OF PERSONS ---------------------------------
//------------------------------------------------------------------------------------------------------------ 
void runSimulation()
{
    for(int k = 0; k < totalSimulationTime; k++){

        // Future status becomes current status for each person in the simulation
        for (int i = 0; i < numberPersons; i++){
            persons[i].status = persons[i].futureStatus;
        }

        // Printing matrix sim after each generation
        #ifdef DEBUG
            displaySimulation(k);
        #endif

        // Update infection matrix
        for(int i = 0; i < numberPersons; i++){
            //Populating the infectedPerson matrix with infected persons. If the person is infected I will put '1' at his position in infectedMatrix so I know that at this position sopmeone is infected
            if(persons[i].status == INFECTED && infectedPersons[persons[i].y][persons[i].x] == 0) infectedPersons[persons[i].y][persons[i].x] = 1;
        }

        // Updating the status based on infection spread for each person in the simulation
        for(int j=0; j < numberPersons; j++){
            // Only susceptible persons can be infected. If the person is Susceptible and at his position in infectedPerson matrix is someone infected (is 1) then the person becomes infected
            if(persons[j].status == SUSCEPTIBLE && infectedPersons[persons[j].y][persons[j].x] > 0){
                updateInfectionStatus(&persons[j]);
                #ifdef DEBUG
                    printf("!!! Got infected the Person %d !!!\n",persons[j].personID);
                #endif
            }
        }

        // Updating the locations for all persons in the area and update their status based on disease progression
        for(int i = 0; i < numberPersons; i++){
            updatePositionOfAPerson(&persons[i], max_x_coord, max_y_coord);
                // Updating the status based on disease progression for each person in the simulation
            updateFutureStatus(&persons[i]);
                //  Reseting the infectedPerson matrix to zero
            infectedPersons[persons[i].y][persons[i].x] = 0;
        }
    }
}

void *runSimParallel(void *rank)
{
    int myRank = *(int *)rank;
    
    if (threadCount > numberPersons) {
        printf("Error: Number of threads exceeds number of persons.\n");
        exit(-1);
    }
    
    int local_n = numberPersons / threadCount;
    int firstPerson = myRank * local_n;
    int lastPerson = (myRank + 1) * local_n - 1;
    // TODO: numberPersons MUST BE DIVISIBLE BY threadCount

    for(int k = 0; k < totalSimulationTime; k++){

        // Apply future status to make it the current status for the next step, for each person in the simulation
        for (int i = firstPerson; i <= lastPerson; i++){
            persons[i].status = persons[i].futureStatus; 
        }
        // Printing matrix sim after each generation
        #ifdef DEBUG
            displaySimulationParallel(k,firstPerson,lastPerson);
        #endif

        pthread_barrier_wait(&mybarrier);

        for(int i = firstPerson; i <= lastPerson; i++){
            if(persons[i].status == INFECTED && infectedPersons[persons[i].y][persons[i].x] == 0) {
                // pthread_mutex_lock(&infectedPersons_mutex);
                infectedPersons[persons[i].y][persons[i].x] = 1;
                // pthread_mutex_unlock(&infectedPersons_mutex);
            }
        }

        pthread_barrier_wait(&mybarrier);

        // Updating the status based on infection spread for each person in the sim
        for(int j=firstPerson; j <= lastPerson; j++){
            // Only susceptible persons can be infected
            if(persons[j].status == SUSCEPTIBLE && infectedPersons[persons[j].y][persons[j].x] > 0){
                pthread_mutex_lock(&infectedPersons_mutex);
                updateInfectionStatus(&persons[j]);
                pthread_mutex_unlock(&infectedPersons_mutex);
                
                #ifdef DEBUG
                    printf("!!! Got infected ID %d !!!\n",persons[j].personID);
                #endif
            }
        }

        pthread_barrier_wait(&mybarrier);

        // Updating the locations for all persons
        for(int i = firstPerson; i <= lastPerson; i++){
            updatePositionOfAPerson(&persons[i],max_x_coord,max_y_coord);
                // Updating the status based on disease progression for each person in the simulation
            updateFutureStatus(&persons[i]);

            // pthread_mutex_lock(&infectedPersons_mutex);
            infectedPersons[persons[i].y][persons[i].x] = 0;
            // pthread_mutex_unlock(&infectedPersons_mutex);
        }
        pthread_barrier_wait(&mybarrier);
    }

    return NULL;
}

//------------------------------------------------------------------------------------------------------------
//-------------------------------------------- PARALLEL SIMULATION OF PERSONS --------------------------------
//------------------------------------------------------------------------------------------------------------ 

void runSimulationParallel()
{
    pthread_t *thread_handles;
    thread_handles = malloc(threadCount * sizeof(pthread_t));
    if(thread_handles == NULL){
        perror("Error allocating memory.\n");
        free(thread_handles);
        exit(-1);
    }

        // Initialize barrier and mutex
    pthread_barrier_init(&mybarrier, NULL, threadCount);
    pthread_mutex_init(&infectedPersons_mutex, NULL);

    int *tid;
    tid = malloc(threadCount * sizeof(int));
    if(tid == NULL){
        perror("Error allocating memory\n");
        free(tid);
        exit(-1);
    }

        //  Creating threads
    for (int thread = 0; thread < threadCount; thread++){
        tid[thread] = thread;
        pthread_create(&thread_handles[thread], NULL, runSimParallel, &tid[thread]);
    }

        //  Waiting the threads to finish their work
    for(int thread = 0; thread < threadCount; thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    
    // Destroying the barrier
    pthread_barrier_destroy(&mybarrier);

        //  Free memory
    free(thread_handles);
    free(tid);
}

//------------------------------------------------------------------------------------------------------------
//-------------------------------------------- FREE MEMORY ---------------------------------------------------
//------------------------------------------------------------------------------------------------------------ 

void free_simulation() {
    free(persons);
}

//------------------------------------------------------------------------------------------------------------
//-------------------------------------------- CHECKING RESULTS' CONSISTENCY ---------------------------------
//------------------------------------------------------------------------------------------------------------ 

int Equal_data(Person *serialPersons, Person *parallelPersons)
{
    for(int i=0;i<numberPersons;i++)
    {
        if(serialPersons[i].personID != parallelPersons[i].personID ||
            serialPersons[i].x != parallelPersons[i].x ||
            serialPersons[i].y != parallelPersons[i].y ||
            serialPersons[i].status != parallelPersons[i].status ||
            serialPersons[i].infectionCounter != parallelPersons[i].infectionCounter ||
            serialPersons[i].infectedTime != parallelPersons[i].infectedTime ||
            serialPersons[i].immuneTime != parallelPersons[i].immuneTime ||
            serialPersons[i].direction != parallelPersons[i].direction) 
            {
                printf("Person %d is not equal with Person parallel %d\n",serialPersons[i].personID,parallelPersons[i].personID);
                printf("Serial person %d (%d,%d): Status= %d; infection counter= %d; infection Time= %d, immune Time= %d\n",
                serialPersons[i].personID,serialPersons[i].x,serialPersons[i].y,serialPersons[i].status,serialPersons[i].infectionCounter,serialPersons[i].infectedTime,serialPersons[i].immuneTime);
                printf("Parallel person %d (%d,%d): Status= %d; infection counter= %d; infection Time= %d, immune Time= %d\n",
                parallelPersons[i].personID, parallelPersons[i].x, parallelPersons[i].y, parallelPersons[i].status,parallelPersons[i].infectionCounter,parallelPersons[i].infectedTime,parallelPersons[i].immuneTime);
                return 0;
            }
    }
    return 1;
}
