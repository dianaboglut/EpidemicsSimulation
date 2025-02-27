#include "person.h"

void updatePositionOfAPerson(Person *p,int max_X,int max_Y)
{   
    //  x is for collumns and y is for lines
    switch (p->direction)
    {
    case 0: // North
        p->y -= p->amplitude;
        if(p->y < 0){
            p->y = -p->y;
            p->direction = 1; // Reverse direction to South
        }
        break;
    case 1: // South
        p->y += p->amplitude;
        if(p->y >= max_Y) {     
            p->y = 2 * max_Y - p->y - 2; // Correcting the position of the person. It should be in the rectangular areap
            p->direction = 0; // Reverse the movement direction. "going back"
        }
        break;
    case 2: // East
        p->x += p->amplitude;
        if(p->x >= max_X){
            p->x = 2 * max_X - p->x - 2;
            p->direction = 3;
        }
        break;
    case 3: // West
        p->x -= p->amplitude;
        if(p->x < 0){
            p->x = -p->x; // Bounce back within boundary
            p->direction = 2;   // Reverse to east
        }
        break;    
    }
}

void updateFutureStatus(Person *p1)
{
    // If the person is infected, the time of his infection will increase
    if(p1->status == INFECTED){   
        p1->infectedTime++;
        
        // Checking if the person should become immune
        if(p1->infectedTime >= INFECTED_DURATION){
            p1->infectedTime = 0;
            p1->futureStatus = IMMUNE;

            #ifdef DEBUG
                printf("# Preson %d got IMMUNE #\n",p1->personID);
            #endif
        }
        else p1->futureStatus = INFECTED; // or remains infected
    }

    // If the person is immune, the immune time will increase
    if(p1->status == IMMUNE){
        p1->immuneTime++;
        // verifing if the person is still immune
        if(p1->immuneTime >= IMMUNE_DURATION){
            p1->immuneTime = 0;
            p1->futureStatus = SUSCEPTIBLE;

            #ifdef DEBUG
                printf("# Person %d became SUSCEPTIBLE #\n",p1->personID);
            #endif
        }
        else p1->futureStatus = IMMUNE;
    }
}

void updateInfectionStatus(Person *p1)
{
    p1->futureStatus = INFECTED;
    p1->infectionCounter ++;

}
