#include "include.h"

void displayMatrixSimulation(int simTime)
{
    char matrix[max_x_coord][max_y_coord];

    // Init matrix
    for(int i = 0; i < max_x_coord; i++){
        for(int j = 0; j < max_y_coord; j++){
            matrix[i][j]='.'; // Empty cell
        }
    }

    // Populate the matrix with the status for every person
    for(int i = 0; i < numberPersons; i++){
        if(persons[i].status == INFECTED) matrix[persons[i].x][persons[i].y] = '0';
        else if (persons[i].status == IMMUNE) matrix[persons[i].x][persons[i].y] = '2';
        else if (persons[i].status == SUSCEPTIBLE)  matrix[persons[i].x][persons[i].y] = '1';    
    }

    printf("\n---------------------\n");
    printf("*** SIMULATION TIME %d ***\n",simTime);
    printf("---------------------\n");
    printf("   ");
    for(int y=0; y < max_y_coord; y++){
        printf("x%d ",y);
    }
    printf("\n");   
    for(int y=0; y < max_y_coord; y++){
        printf("y%d  ",y);
        for(int x=0; x < max_x_coord; x++){
            printf("%c  ",matrix[x][y]);
        }
        printf("\n");
    }
    printf("---------------------\n");
}

void displaySimulation(int simTime)
{
    printf("\n*** SIMULATION TIME %d ***\n",simTime);
    printf("------------------------\n");
    for (int i = 0; i < numberPersons; i++){
        printf("ID: %d -> ",persons[i].personID);
        printf("(%d, %d); Status: %d; Inf. Counter: %d; ",persons[i].x,
                                                        persons[i].y,
                                                        persons[i].status,
                                                        persons[i].infectionCounter);
        printf("Inf. Time: %d; Immune Time: %d\n", persons[i].infectedTime,
                                                    persons[i].immuneTime);
        printf("----------------------------------------------------------------------------------\n");
    }
    printf("\n");
}

void displaySimulationParallel(int simTime, int firstPerson, int lastPerson)
{
    printf("\n*** SIMULATION TIME %d ***\n",simTime);
    printf("------------------------\n");
    for (int i = firstPerson; i <= lastPerson; i++){
        printf("ID: %d -> ",persons[i].personID);
        printf("(%d, %d); Status: %d; Inf. Counter: %d; ",persons[i].x,
                                                        persons[i].y,
                                                        persons[i].status,
                                                        persons[i].infectionCounter);
        printf("Inf. Time: %d; Immune Time: %d\n", persons[i].infectedTime,
                                                    persons[i].immuneTime);
        printf("----------------------------------------------------------------------------------\n");
    }
    printf("\n");
}
