#include "Func.h"
#include <stdbool.h>


//Modos de funcionamient
uint8 Exploration(int* x, int* y, int* orient, int flood[][10], int* state, int L,int R,int F, int cells[][10], bool* shorta, int flood2[][10], int* queue, int* MainQueue, int Surrounds[8]){
    int xprev=0;int yprev=0;
    char direction;

    //si ingresa un nuevo valor por el UART se comprueba si se tiene activado el valor de "valor nuevo" si esta variable global es 1 entonces se procede a ejecutar el valor del modo
    updateWalls( *x, *y, *orient, L, R, F,cells);
    
    //if (flood[x][y]!=0){
    //    floodFill(x,y,xprev,yprev)};
    //else: no me acuerdo, revisar diagrama de flujo
        
    if (flood[*y][*x] != 0) {// si no está en el centro actualiza
        switch (*state) {
        case 0:
            appendZero(flood,MainQueue);//falta revisar los appends
            break;
        case 1:
            appendDestination(15, 0,flood,MainQueue);
            *shorta = false;
            break;
        case 2:
            appendDestination(0, 0,flood,MainQueue);
            *shorta = false;
            break;
        case 3:
            appendZero(flood,MainQueue);
            floodFill2(x,y,cells,flood,Surrounds,flood2);
            *shorta = true;
            break;
        case 4:
            appendDestination(0, 15);
            *shorta = false;
            break;
        case 5:
            appendDestination(0, 0);
            *shorta = false;
            break;
        case 6:
            appendZero();
            floodFill2(flood2);
            *shorta = true;
            break;
        }
        floodFill3(flood, queue);
    }
    else {
        switch (*state) {
        case 5:
            appendZero();
            floodFill3(flood, queue);
            *state = *state + 1;
            break;
        case 4:
            changeDestination(flood, 0, 0);
            *state = *state + 1;
            break;
        case 3:
            changeDestination(flood, 0, 15);
            *state = *state + 1;
            break;
        case 2:
            appendZero();
            floodFill3(flood, queue);
            *state = *state + 1;
            break;
        case 1:
            changeDestination(flood, 0, 0);
            *state = *state + 1;
            break;
        case 0:
            //center(x,y,xprev,yprev,orient,flod)//this function should modify x,y,xprev,yprev,orient so these are passed by reference

            changeDestination(flood, 15, 0);
            *state = *state + 1;
            break;
        }
        floodFill2(flood2);
    }

    
    //se  toma la decision de adonde ir 
    if (*shorta) {
        direction = toMove2(flood2, x, y, xprev, yprev, orient);
    }
    else {
        direction = toMove(flood, x, y, xprev, yprev, orient);
    }
    //update orient
    
        //de acuerdo a si se decide que se debe girar se decide se va armando el vector de decisiones 
    if (direction == 'L') {
        //API_turnLeft();
        orientation(orient, 'L');
    }
    else if (direction == 'R') {
        //API_turnRight();
        //orient = orientation(orient, 'R');
    }
    else if (direction == 'B') {
        //API_turnLeft();
        //orient = orientation(orient, 'L');
        //API_turnLeft();
        //orient = orientation(orient, 'L'); 
    }
    //API_moveForward();
    
        //se actualizan los valores
    xprev = *x;
    yprev = *y;
    updateCoords(x, y, orient);
    
    uint8 OrderMovement = codification(direction);
    
}