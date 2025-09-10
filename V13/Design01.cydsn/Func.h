#define SIZE 10
#include "project.h"


void resetValues( ){//not used

    int x = 0, y = 0, orient = 0;
    int cells[SIZE][SIZE] = {0};
    int cell = 0;
    int flood[SIZE][SIZE] = {//laberinto chiquito
        {8,7,6,5,4,4,5,6,7,8},
        {7,6,5,4,3,3,4,5,6,7},
        {6,5,4,3,2,2,3,4,5,6},
        {5,4,3,2,1,1,2,3,4,5},
        {4,3,2,1,0,0,1,2,3,4},
        {4,3,2,1,0,0,1,2,3,4},
        {5,4,3,2,1,1,2,3,4,5},
        {6,5,4,3,2,2,3,4,5,6},
        {7,6,5,4,3,3,4,5,6,7},
        {8,7,6,5,4,4,5,6,7,8}
    };
};



void updateWalls(int x, int y, int orient, int L, int R, int F, int cells[][10])  {
  
    
    if (L && R && F) {
        if (orient == 0) cells[y][x] = 13;
        else if (orient == 1) cells[y][x] = 12;
        else if (orient == 2) cells[y][x] = 11;
        else if (orient == 3) cells[y][x] = 14;
    } else if (L && R && !F) {
        if (orient == 0 || orient == 2) cells[y][x] = 9;
        else if (orient == 1 || orient == 3) cells[y][x] = 10;
    } else if (L && F && !R) {
        if (orient == 0) cells[y][x] = 8;
        else if (orient == 1) cells[y][x] = 7;
        else if (orient == 2) cells[y][x] = 6;
        else if (orient == 3) cells[y][x] = 5;
    } else if (R && F && !L) {
        if (orient == 0) cells[y][x] = 7;
        else if (orient == 1) cells[y][x] = 6;
        else if (orient == 2) cells[y][x] = 5;
        else if (orient == 3) cells[y][x] = 8;
    } else if (F) {
        if (orient == 0) cells[y][x] = 2;
        else if (orient == 1) cells[y][x] = 3;
        else if (orient == 2) cells[y][x] = 4;
        else if (orient == 3) cells[y][x] = 1;
    } else if (L) {
        if (orient == 0) cells[y][x] = 1;
        else if (orient == 1) cells[y][x] = 2;
        else if (orient == 2) cells[y][x] = 3;
        else if (orient == 3) cells[y][x] = 4;
    } else if (R) {
        if (orient == 0) cells[y][x] = 3;
        else if (orient == 1) cells[y][x] = 4;
        else if (orient == 2) cells[y][x] = 1;
        else if (orient == 3) cells[y][x] = 2;
    }
    else{cells[y][x] = 15;}
}//should work

_Bool isAccessible(int x, int y, int x1, int y1, int cells[][10]) {
    if (x == x1) {
        if (y > y1) {
            return !(cells[y][x] == 4 || cells[y][x] == 5 || cells[y][x] == 6 || cells[y][x] == 10 || cells[y][x] == 11 || cells[y][x] == 12 || cells[y][x] == 14);
        } else {
            return !(cells[y][x] == 2 || cells[y][x] == 7 || cells[y][x] == 8 || cells[y][x] == 10 || cells[y][x] == 12 || cells[y][x] == 13 || cells[y][x] == 14);
        }
    } else if (y == y1) {
        if (x > x1) {
            return !(cells[y][x] == 1 || cells[y][x] == 5 || cells[y][x] == 8 || cells[y][x] == 9 || cells[y][x] == 11 || cells[y][x] == 13 || cells[y][x] == 14);
        } else {
            return !(cells[y][x] == 3 || cells[y][x] == 6 || cells[y][x] == 7 || cells[y][x] == 9 || cells[y][x] == 11 || cells[y][x] == 12 || cells[y][x] == 13);
        }
    }
    return 0;
}

void getSurrounds(int x, int y, int surrounds[8]) {//sorrounds are the 4 cells next to the current cell
	surrounds[0] = x;    //x0
	surrounds[1] = y + 1;//y0
	surrounds[2] = x + 1;//x1
	surrounds[3] = y;    //y1
	surrounds[4] = x;    //x2
	surrounds[5] = y - 1;//y2
    surrounds[6] = x - 1;//x3
	surrounds[7] = y;    //y3

    if (surrounds[2] >= SIZE) surrounds[2] = -1;
    if (surrounds[1] >= SIZE) surrounds[1] = -1;
}



_Bool isConsistent(int x, int y, int flood[][10], int cells[][10]) {
    int surrounds[8];
    getSurrounds(x, y, surrounds);

    int val = flood[y][x];
    int minVals[4] = {-1, -1, -1, -1};

    if (surrounds[0] >= 0 && surrounds[1] >= 0 && isAccessible(x, y, surrounds[0], surrounds[1],cells))
	minVals[0] = flood[surrounds[1]][surrounds[0]];
    if (surrounds[2] >= 0 && surrounds[3] >= 0 && isAccessible(x, y, surrounds[2], surrounds[3],cells))
	minVals[1] = flood[surrounds[3]][surrounds[2]];
    if (surrounds[4] >= 0 && surrounds[5] >= 0 && isAccessible(x, y, surrounds[4], surrounds[5],cells))
	minVals[2] = flood[surrounds[5]][surrounds[4]];
    if (surrounds[6] >= 0 && surrounds[7] >= 0 && isAccessible(x, y, surrounds[6], surrounds[7],cells))
	minVals[3] = flood[surrounds[7]][surrounds[6]];

    int minCount = 0;
    for (int i = 0; i < 4; i++) {
        if (minVals[i] == -1) continue;
        if (minVals[i] == val + 1) continue;
        if (minVals[i] == val - 1) minCount++;
    }

    return minCount > 0;
}

void makeConsistent(int x, int y,int flood[][10], int cells[][10], int surrounds[8]) {
    
    getSurrounds(x, y, surrounds);

    int val = flood[y][x];
    int minVals[4] = {-1, -1, -1, -1};

    if (surrounds[0] >= 0 && surrounds[1] >= 0 && isAccessible(x, y, surrounds[0], surrounds[1],cells)) minVals[0] = flood[surrounds[1]][surrounds[0]];
    if (surrounds[2] >= 0 && surrounds[3] >= 0 && isAccessible(x, y, surrounds[2], surrounds[3],cells)) minVals[1] = flood[surrounds[3]][surrounds[2]];
    if (surrounds[4] >= 0 && surrounds[5] >= 0 && isAccessible(x, y, surrounds[4], surrounds[5],cells)) minVals[2] = flood[surrounds[5]][surrounds[4]];
    if (surrounds[6] >= 0 && surrounds[7] >= 0 && isAccessible(x, y, surrounds[6], surrounds[7],cells)) minVals[3] = flood[surrounds[7]][surrounds[6]];

    for (int i = 0; i < 4; i++) {
        if (minVals[i] == -1) minVals[i] = 1000;
    }

    int minVal = minVals[0];
    for (int i = 1; i < 4; i++) {
        if (minVals[i] < minVal) minVal = minVals[i];
    }

    flood[y][x] = minVal + 1;
}

void floodFill(int x, int y, int xprev, int yprev, int cells[][10], int flood[][10], int surrounds[8]) {//corregir uso de stack
    if (!isConsistent(x, y,flood,cells)) {
        flood[y][x] = flood[yprev][xprev] + 1;
    }

    int stack[SIZE * 3];
    int top = -1;
    stack[++top] = x;
    stack[++top] = y;

    //int surrounds[8];
    getSurrounds(x, y, surrounds);
    for (int i = 0; i < 8; i += 2) {
        if (surrounds[i] >= 0 && surrounds[i + 1] >= 0 && isAccessible(x, y, surrounds[i], surrounds[i + 1],cells )) {
            stack[++top] = surrounds[i];
            stack[++top] = surrounds[i + 1];
        }
    }

    while (top >= 0) {
        int yrun = stack[top--];
        int xrun = stack[top--];

        if (isConsistent(xrun, yrun,flood,cells)) {
            continue;
        } else {
            makeConsistent(xrun, yrun,flood,cells,surrounds);
            stack[++top] = xrun;
            stack[++top] = yrun;

            getSurrounds(xrun, yrun, surrounds);
            for (int i = 0; i < 8; i += 2) {
                if (surrounds[i] >= 0 && surrounds[i + 1] >= 0 && isAccessible(xrun, yrun, surrounds[i], surrounds[i + 1],cells)) {
                    stack[++top] = surrounds[i];
                    stack[++top] = surrounds[i + 1];
                }
            }
        }
    }
}

void floodFill2(int x, int y, int cells[][10], int maze[][10], int surrounds[8], int flood2[][10]) {//corregir uso de stack
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
           maze[i][j]=0; 
        };
    };
    
    int stack[SIZE * 3];
    int top = -1;

    
    flood2[4][4]=1;
    flood2[5][4]=1;
    flood2[4][5]=1;
    flood2[5][5]=1;
    
    stack[++top] = 4;
    stack[++top] = 4;
    stack[++top] = 5;
    stack[++top] = 4;
    stack[++top] = 4;
    stack[++top] = 5;
    stack[++top] = 5;
    stack[++top] = 5;
    
    int iterador=top;
    
    while (iterador >= 0) {
        int yrun = stack[top--];
        int xrun = stack[top--];
        getSurrounds(x, y, surrounds);
       
        if (surrounds[0]>=0 && surrounds[1]>=0 && (cells[surrounds[1]][surrounds[0]] != 0 ) ) {
            if (maze[surrounds[1]][surrounds[0]] == 0){
                if (isAccessible(xrun,yrun,surrounds[0], surrounds[1],cells)){
                    maze[surrounds[1]][surrounds[0]]= maze[yrun][xrun]+1;
                    stack[++top]=surrounds[1];
                    stack[++top]=surrounds[0];
                };
            };
        }

        if (surrounds[2] >= 0 && surrounds[3] >= 0 && (cells[surrounds[3]][surrounds[2]] != 0)) {
            if (maze[surrounds[3]][surrounds[2]] == 0) {
                if (isAccessible(xrun, yrun, surrounds[2], surrounds[3], cells)) {
                    maze[surrounds[3]][surrounds[2]] = maze[yrun][xrun] + 1;
                    stack[++top] = surrounds[3];
                    stack[++top] = surrounds[2];
                }
            }
        }

        if (surrounds[4] >= 0 && surrounds[5] >= 0 && (cells[surrounds[5]][surrounds[4]] != 0)) {
            if (maze[surrounds[5]][surrounds[4]] == 0) {
                if (isAccessible(xrun, yrun, surrounds[4], surrounds[5], cells)) {
                    maze[surrounds[5]][surrounds[4]] = maze[yrun][xrun] + 1;
                    stack[++top] = surrounds[5];
                    stack[++top] = surrounds[4];
                }
            }
        }

        if (surrounds[6] >= 0 && surrounds[7] >= 0 && (cells[surrounds[7]][surrounds[6]] != 0)) {
            if (maze[surrounds[7]][surrounds[6]] == 0) {
                if (isAccessible(xrun, yrun, surrounds[6], surrounds[7], cells)) {
                    maze[surrounds[7]][surrounds[6]] = maze[yrun][xrun] + 1;
                    stack[++top] = surrounds[7];
                    stack[++top] = surrounds[6];
                }
            }
        }
        iterador--;
    }
}

void floodFill3(int maze[SIZE][SIZE], int* queue, int tamannoQueue, int surrounds[8], int cells[][10]) {
    int stack[SIZE * 3];
    int top = -1;

    
    while (tamannoQueue != 0) {
        int yrun = stack[tamannoQueue--];
        int xrun = stack[tamannoQueue--];
        
        getSurrounds(xrun, yrun,surrounds);
        
        for (int i = 0; i < 8; i += 2) {
            int x = surrounds[i];
            int y = surrounds[i + 1];

            if (x >= 0 && y >= 0) {
                if (maze[y][x] == 255) {
                    if (isAccessible(xrun, yrun, x, y,cells)) {
                        maze[y][x] = maze[yrun][xrun] + 1;
                        queue[tamannoQueue++] = y;
                        queue[tamannoQueue++] = x;
                    }
                }
            }
        }
    }
}








void orientation(int* orient, char turning) {//modify orientation

    if (turning == 'L') {//gira a la izquierda
        if (*orient != 0) {//se aplica esta condicion ya que de otra manera llega a negativo y estamos trabajando con unsigned
            (*orient) --;
        }
        else {
            *orient = 3;
        }
    }

    if (turning == 'R') {//gira a la derecha
        if (*orient != 3) {//solo se aplica esta estructura para que se mantenga el rango de valores entre 0 y 3
            (*orient)++;
        }
        else {
            *orient = 0;
        }
    }
    
    if (turning == 'B') {//giro de 180
        // NOTA: Se corrigió este switch. Le faltaban los 'break' y estaba incorrecto.
        switch( *orient ){
            case 0: *orient=2; break;
            case 1: *orient=3; break;
            case 2: *orient=0; break;
            case 3: *orient=1; break;
        }
    }
    
}

void updateCoords(int* x, int* y, int* orient) {//use only if the robot moves forward.
    switch (*orient) {
        case 0:
            // Move forward in the direction of orientation 0
            (*y)++;
            break;
        case 1:
            // Move forward in the direction of orientation 1
            (*x)++;
            break;
        case 2:
            // Move forward in the direction of orientation 2
            (*y)--;
            break;
        case 3:
            // Move forward in the direction of orientation 3
            (*x)--;
            break;
        default:
            // Handle invalid orientation (optional)
            break;
    }
}


char toMove(int flood[][10],int* x, int* y, int* xprev,int* yprev,int* orient,int surrounds[8],int cells[][10]){
    getSurrounds(*x,*y, surrounds);
    int value= flood[*y][*x];
    int prev=0;
    int minVals[4]={1000,1000,1000,1000};
    int minVal;
    int noMovements=0;
    int minCell=0;
        
    if (isAccessible(*x,*y,surrounds[0],surrounds[1],cells) ){//se envia el dato de x y y, no el ptr
        if(surrounds[0]==*xprev & surrounds[1]==*yprev ){prev=0; minVals[0]=flood[*yprev][*xprev];}}
    
    if (isAccessible(*x,*y,surrounds[2],surrounds[3],cells) ){
        if(surrounds[2]==*xprev & surrounds[3]==*yprev ){prev=1; minVals[1]=flood[*yprev][*xprev];}}
    
    if (isAccessible(*x,*y,surrounds[4],surrounds[5],cells) ){
        if(surrounds[4]==*xprev & surrounds[5]==*yprev ){prev=1; minVals[2]=flood[*yprev][*xprev];}}
    
    if (isAccessible(*x,*y,surrounds[6],surrounds[7],cells) ){
        if(surrounds[6]==*xprev & surrounds[7]==*yprev ){prev=1; minVals[3]=flood[*yprev][*xprev];}}
    
    minVal=minVals[0];
    
    for (int i=0;i<=4;i++){
    if (minVals[i]!=1000){noMovements++;}}
    
    for (int i=0;i<=4;i++){
        if (minVals[i]<minVal){
            if (noMovements==1){
                minVal=minVals[i];
                minCell=i;
            }
            else{
                if (i==prev){}
                else{
                    minVal= minVals[i];minCell=i;
                };
            }
        }
    }
        if (minCell == *orient) {
        return 'F';
        } else if ((minCell == *orient - 1) || (minCell == *orient + 3)) {
        return 'L';
        } else if ((minCell == *orient + 1) || (minCell == *orient - 3)) {
        return 'R';
        } else {
        return 'B';
    }
    
}

char toMove2(int flood2[][10],int* x, int* y,int* orient,int surrounds[8],int cells[][10]){
    getSurrounds(*x,*y, surrounds);
    int value= flood2[*y][*x];
    int prev=0;
    int minVals[4]={1000,1000,1000,1000};
    int minVal;
    int noMovements=0;
    int minCell=0;
    
    if (isAccessible(*x,*y,surrounds[0],surrounds[1],cells) ){
        if(flood2[surrounds[1]][surrounds[0]]==value-1 ){
            minCell=0;
        }
    }
    
    if (isAccessible(*x,*y,surrounds[2],surrounds[3],cells) ){
        if(flood2[surrounds[3]][surrounds[2]]==value-1 ){
            minCell=1;
        }
    }
    
    if (isAccessible(*x,*y,surrounds[4],surrounds[5],cells) ){
        if(flood2[surrounds[5]][surrounds[4]]==value-1 ){
            minCell=2;
        }
    }
    
    if (isAccessible(*x,*y,surrounds[6],surrounds[7],cells) ){
        if(flood2[surrounds[7]][surrounds[6]]==value-1 ){
            minCell=3;
        }
    }
    
        if (minCell == *orient) {
        return 'F';
        } else if ((minCell == *orient - 1) || (minCell == *orient + 3)) {
        return 'L';
        } else if ((minCell == *orient + 1) || (minCell == *orient - 3)) {
        return 'R';
        } else {
        return 'B';
    }
    
}
//falta definir center

void appendZero(int flood[][10], int* queue) {
    int i, j;
    
    // Initialize flood array
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            flood[i][j] = 255;
        }
    }
    
    // Set specific positions to 0
    flood[7][7] = 0;
    flood[8][7] = 0;
    flood[7][8] = 0;
    flood[8][8] = 0;
    
    // Initialize queue with specific coordinates
    int queueIndex = 0;
    queue[queueIndex++] = 7;
    queue[queueIndex++] = 7;
    queue[queueIndex++] = 8;
    queue[queueIndex++] = 7;
    queue[queueIndex++] = 7;
    queue[queueIndex++] = 8;
    queue[queueIndex++] = 8;
    queue[queueIndex++] = 8;
}

void appendDestination(int x, int y, int flood[][10],int *queue) {
    int i, j;
    
    // Initialize flood array
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            flood[i][j] = 255;
        }
    }
    
    // Set destination position to 0
    flood[y][x] = 0;
    
    // Add destination coordinates to queue
    int queueIndex = 0;
    queue[queueIndex++] = y;
    queue[queueIndex++] = x;
}


uint8 codification(char direction){//, int* messageSent){
    uint8 order;
    //if (*messageSent == 0){
        if (direction == 'L'){order=0b00100100;}
        if (direction == 'B'){order=0b00101000;}
        if (direction == 'R'){order=0b00100001;}
        if (direction == 'F'){order=0b00100010;}
    //}
    return order;
}


    
    
    









