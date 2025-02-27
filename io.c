#include "io.h"

void readInput(char *fileName)
{
    FILE *file=fopen(fileName,"r");
    if(file==NULL){
        printf("Error opening the file.\n");
        exit(-1);
    }

    // Read the size of the simulation area
    fscanf(file,"%d %d",&max_x_coord, &max_y_coord);

    // Read the number of persons in the simulation
    fscanf(file,"%d",&numberPersons);

    // To be able to reset
    if(persons != NULL) {
        free(persons);
    }

    // Allocate memory for the person
    persons=malloc(numberPersons*sizeof(Person)); 
    
    if(persons==NULL)
    {
        perror("Error alocating memory for the persons.");
        fclose(file);
        exit(-1);
    }

    for(int i = 0; i < numberPersons; i++)
    {
        fscanf(file,"%d %d %d %d %d %d",&persons[i].personID,
                                        &persons[i].x,
                                        &persons[i].y,
                                        &persons[i].status,
                                        &persons[i].direction,
                                        &persons[i].amplitude);
        persons[i].infectionCounter=0;
        persons[i].futureStatus=persons[i].status;
        persons[i].immuneTime=0;
        persons[i].infectedTime=0;
    }
    fclose(file);
}

void writeFileSerial(char *inputFileName, int totalSimTime)
{
    char outputFileName[1024];
    char fileName[512] = {0};

    strcpy(fileName, inputFileName);
    fileName[strlen(inputFileName) - 4] = '\0';
    fileName[strlen(inputFileName) - 3] = '\0';
    fileName[strlen(inputFileName) - 2] = '\0';
    fileName[strlen(inputFileName) - 1] = '\0';

    snprintf(outputFileName,sizeof(outputFileName),"%s_serial_out.txt",fileName);
    
    FILE* file=fopen(outputFileName,"w");
    if(file == NULL){
        perror("Can not write in serial file.");
        exit(-1);
    }

    for(int i = 0; i < numberPersons; i++){
        fprintf(file,"Person %d:\n\tFinal coordinates (%d, %d)\n\tStatus: %d\n\tInfection Counter for a simulation time equal to %d: %d\n", persons[i].personID,
                                                                                                                                            persons[i].x,
                                                                                                                                            persons[i].y,
                                                                                                                                            persons[i].status,
                                                                                                                                            totalSimTime,
                                                                                                                                            persons[i].infectionCounter);
    }

    fclose(file);
}

void writeFileParallel(char *inputFileName, int totalSimTime)
{
    char outputFileName[1024];
    char fileName[512] = {0};

    strcpy(fileName, inputFileName);
    fileName[strlen(inputFileName) - 4] = '\0';
    fileName[strlen(inputFileName) - 3] = '\0';
    fileName[strlen(inputFileName) - 2] = '\0';
    fileName[strlen(inputFileName) - 1] = '\0';

    snprintf(outputFileName,sizeof(outputFileName),"%s_parallel_out.txt",fileName);
    
    FILE* file=fopen(outputFileName,"w");
    if(file == NULL){
        perror("Can not write in serial file.");
        exit(-1);
    }

    for(int i = 0; i < numberPersons; i++){
        fprintf(file,"Person %d:\n\tFinal coordinates (%d, %d)\n\tStatus: %d\n\tInfection Counter for a simulation time equal to %d: %d\n", persons[i].personID,
                                                                                                                                            persons[i].x,
                                                                                                                                            persons[i].y,
                                                                                                                                            persons[i].status,
                                                                                                                                            totalSimTime,
                                                                                                                                            persons[i].infectionCounter);
    }

    fclose(file);
}
