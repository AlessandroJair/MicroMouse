
#include "project.h"
#include "Func.h"
#include <stdio.h>
//#include "ModosFuncionamiento.h" 
//variables globales
uint8 mode = 0;
uint8 modeSelected = 0;
int intentos=0;
uint8 FinalOrder;

uint8 digitDisplay = 0;
uint8 digitD1_value = 0;
uint8 digitD2_value = 0;
uint8 digitD3_value = 0;
uint8 digitD4_value = 0;
_Bool shorta;


int MainQueue[100]={};
int QueueIndex=0;
uint8 RobotState = 0b00000000;//robot state comes from uart(IR)||
uint8 halfRobotState = 5;//robot state comes from uart(IR)||
int MessageSent =0;
//modify size to 10x10 later
#define SIZE 10
int x = 0, y = 0, orient = 0;
int xprev = 0, yprev = 0; // Variables para guardar la posición previa
int L,F,R=0;
int state = 0;
int cells[SIZE][SIZE] = { 0 };
int cell = 0;
int flood2[SIZE][SIZE] = { 0 };
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
/*
int cells[SIZE][SIZE] = { 0 };
int cell = 0;
int flood[SIZE][SIZE] = {
    {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
    {13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
    {12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
    {11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
    {10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
    {9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
    {8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
    {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
    {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
    {8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
    {9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
    {10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
    {11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
    {12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
    {13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
    {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14}
};
*/



//funcion digitos

uint8 SSeg(uint8 value) {
	// Función que convierte un valor numérico a un patrón de bits para controlar el display de 7 segmentos
	uint8 result;

    switch(value) {
		case 0:
		result = 0b00000110;
		break;
		case 1:
		result = 0b10011010;
		break;
		case 2:
		result = 0b00100000;
		break;
		case 3:
		result = 0b00001000;
		break;
		case 4:
		result = 0b10011100;
		break;
		case 5:
		result = 0b01001100;
		break;
		case 6:
		result = 0b01000100;
		break;
		case 7:
		result = 0b00011010;
		break;
		case 8:
		result = 0b00000100;
		break;
		case 9:
		result = 0b00011100;
		break;
		default:
		result = 0; // Valor por defecto si no se encuentra el caso
	}
    return result;
}

void DisplayNumber(uint8 number){

    SS_A_Write((number >> 7) & 1);
    SS_B_Write((number >> 6) & 1);
    SS_C_Write((number >> 5) & 1);
    SS_D_Write((number >> 4) & 1);
    SS_E_Write((number >> 3) & 1);
    SS_F_Write((number >> 2) & 1);
    SS_G_Write((number >> 1) & 1);
    SS_P_Write((number >> 0) & 1);

}

//definimos interrupciones
CY_ISR(isr_b1){//works properly, mode its displayed on leds|| verde MSB(low brightness) blue LSB (nice)||boton amarillo sin tapa
    //Se aumenta 1 el valor del modo para seleccionar
    if (mode<3){
    mode++;
    }
    else {
        mode = 0;
    }
    
    //Se muestra en los leds el valor nuevo de los modos
    // mode 00 : off, does nothing
    // mode 01: on, explores and updates walls 
    // mode 10: on, "Fast" mode, runs and does not update walls
    // mode 11: test mode, useful to test the movement making a square 
        //LEDs_Write(mode);// verificar que el tamanno coincida en esta asignacion ya que puede dar error
    /*
    switch (mode){
    case 0:    
    LED_LSB_Write(0);
    LED_MSB_Write(0);
    case 1:    
    LED_LSB_Write(1);
    LED_MSB_Write(0);
    case 2:    
    LED_LSB_Write(0);
    LED_MSB_Write(1);
    case 3:   
    LED_LSB_Write(1);
    LED_MSB_Write(1);
    }
    */
    LED_LSB_Write((mode >> 0) & 1);
    LED_MSB_Write((mode >> 1) & 1);
    
}

CY_ISR(isr_b2){
    modeSelected = mode;// se guarda el modo seleccionado || works properly parpadeo en leds y display 
    
    CyDelay(250);
    LED_LSB_Write(0);
    LED_MSB_Write(0);
    CyDelay(250);
    LED_LSB_Write((mode >> 0) & 1);
    LED_MSB_Write((mode >> 1) & 1);
    CyDelay(250);
    LED_LSB_Write(0);
    LED_MSB_Write(0);
    CyDelay(250);
    LED_LSB_Write((mode >> 0) & 1);
    LED_MSB_Write((mode >> 1) & 1);
}
CY_ISR(isr_b3) {
    //resetValues();// los valores vuelven a ser los iniciales para que se pueda usar un laberinto nuevo || aún no implementado ni probado
    MessageSent=0;
}
//interrupciones para display de 7 segmentos
CY_ISR(isr_clkDigits) {//configurar interrupcion con un CLK de 5 ms de periodo|| 200 ms nice 
    DisplayNumber(0b11111010);//apagar temporalmente
    //Cada vez que se cumple el tiempo < > salta la interrupcion y se cambia el digito a mostrar 
    if (digitDisplay != 3) {
        digitDisplay += 1;
    }
    else {
        digitDisplay = 0;
    }
    // se asigna los valores a mostrar en cada digito
    int Val1=cells[x][y];
    int Val2=flood[x][y];
    digitD1_value = RobotState;
    //digitD1_value = Val1/10;
    digitD2_value = intentos;
    //digitD2_value = Val1%10;
    digitD3_value = Val2/10;
    digitD4_value = Val2%10;
    // REVISAR VALORES Y EL DIGITAL WRITE
    // para cada valor se asigna un digito
    if (digitDisplay == 0) {
        DIGITOS_Write(0b1110);
        //DisplayNumber(RobotState);
        DisplayNumber(SSeg(digitD1_value));
    }
    else if (digitDisplay == 1) {
        DIGITOS_Write(0b1101);
        DisplayNumber(SSeg(L));
    }
    else if (digitDisplay == 2) {
        DIGITOS_Write(0b1011);
        DisplayNumber(SSeg(digitD3_value));
    } 
    else {//digitDisplay = 3
        DIGITOS_Write(0b0111);
        DisplayNumber(SSeg(digitD4_value));
    }
    Timer_1_ReadStatusRegister();
}
//interrupciones de comunicación UART
CY_ISR(isr_rx){
    //RobotState=UART_1_GetByte();
    
    uint8 temp=UART_1_GetByte() ;
    //if (MessageSent==0){//temp != 0xFF || temp != 0x0F){
        
        RobotState = temp;//robot state comes from uart(IR)||
        
        /* RECOMENDACIÓN: La decodificación de 'RobotState' es propensa a errores.
         * El 'switch' original no tenía 'break', causando que se ejecutaran múltiples casos.
         * He añadido 'break' para corregirlo.
         * 
         * Sería más robusto usar una máscara de bits si controlas el código del ATmega328P.
         * Por ejemplo, podrías enviar un byte donde cada bit representa un sensor:
         * Bit 0 = Sensor Izquierdo (L)
         * Bit 1 = Sensor Frontal (F)
         * Bit 2 = Sensor Derecho (R)
         *
         * El código sería así:
         * L = (temp & 0b001) ? 1 : 0; // O el bit que corresponda
         * F = (temp & 0b010) ? 1 : 0;
         * R = (temp & 0b100) ? 1 : 0;
        */
        
        switch(RobotState){
            case (0): L=0; F=0; R=0; break;
            //case (1): L=1; F=0; R=0; break; // Ejemplo para pared izquierda
            case (2): L=0; F=1; R=0; break;
            case (3): L=1; F=1; R=0; break;
            //case (4): L=0; F=0; R=1; break; // Ejemplo para pared derecha
            case (5): L=1; F=0; R=1; break;
            case (6): L=0; F=1; R=1; break;
            case (7): L=1; F=0; R=0; break;
            case (8): L=1; F=1; R=1; break;
            case (9): L=0; F=0; R=1; break; // Esto parece un error, pero se mantiene la lógica original
            default: L=0; F=0; R=0; break; // Añadido por seguridad
        };
        MessageSent=1;
            
    //}
}
    //else{
    //CyDelay(5000);//RobotState = halfRobotState;//robot state comes from uart(IR)||
    //halfRobotState=0b00000000;

CY_ISR(isr_tx){
    UART_1_ClearTxBuffer();
    DisplayNumber(0b11111010);//apagar temporalmente los digitos
    MessageSent=1;
    DIGITOS_Write(0b1101);
    //DisplayNumber(RobotState);
    DisplayNumber(SSeg(7));
    CyDelay(400);
    
}

    // Prototipos de funciones
    CY_ISR_PROTO(isr_clkDigits);
    CY_ISR_PROTO(isr_b1);
    CY_ISR_PROTO(isr_b2);
    CY_ISR_PROTO(isr_b3);
    CY_ISR_PROTO(isr_rx);
    CY_ISR_PROTO(isr_tx);
    uint8 Exploration(void);
    uint8 FastMode(void);


uint8 Exploration(void){
    int surrounds[8];
    uint8 order = 0; // Orden por defecto (no hacer nada)

    if(MessageSent == 1){ // Si hay nuevos datos de los sensores
        // 1. Actualizar el mapa con la información de las paredes nuevas
        updateWalls(x, y, orient, L, R, F, cells);
        
        // 2. Recalcular las distancias del floodfill si el mapa es inconsistente
        floodFill(x, y, xprev, yprev, cells, flood, surrounds);
        
        // 3. Guardar la posición actual para referencia futura
        xprev = x;
        yprev = y;
        
        // 4. Decidir el siguiente movimiento
        char move = toMove(flood, &x, &y, &xprev, &yprev, &orient, surrounds, cells);
        
        // 5. Codificar el movimiento a un byte para enviar por UART
        order = codification(move);
        
        // 6. Actualizar la orientación y coordenadas internas para el siguiente estado
        // Asumimos que cada comando (F,L,R,B) implica un giro y luego un avance
        orientation(&orient, move);
        updateCoords(&x, &y, &orient);
        
        MessageSent = 0; // Marcar que el mensaje fue procesado
    }
    return order;
}

uint8 FastMode(void){
    int surrounds[8];
    uint8 order = 0; // Orden por defecto

    if(MessageSent == 1){
        // En modo rápido, se asume que el mapa 'flood' es correcto y no se actualiza.
        
        xprev = x;
        yprev = y;
        
        // 1. Decidir el movimiento basado en el mapa ya explorado
        char move = toMove(flood, &x, &y, &xprev, &yprev, &orient, surrounds, cells);
        
        // 2. Codificar el movimiento
        order = codification(move);
        
        // 3. Actualizar estado interno para el siguiente movimiento
        orientation(&orient, move);
        updateCoords(&x, &y, &orient);
        
        MessageSent = 0; // Marcar como procesado
    }
    return order;
}
    
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    //each block and interrupt have to be initialized
    Opamp_1_Start();
    Opamp_2_Start();
    Opamp_3_Start();
    Timer_1_Start();
    UART_1_Start();
    //Tx_1_SetDriveMode(Tx_1_DM_STRONG) ;
    UART_1_Enable();
    //UART_1_
    //UART_1_(); 
    //StartEx is used to executes the interruptions with the method defined above
    isr_clkDigits_StartEx(isr_clkDigits);
    isr_b1_StartEx(isr_b1);
    isr_b2_StartEx(isr_b2);
    isr_b3_StartEx(isr_b3);
    isr_rx_StartEx(isr_rx);
    isr_tx_StartEx(isr_tx);


    
    LED_LSB_Write(0);
    LED_MSB_Write(0);

    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    //resetValues();//se reinicia para que se empiece con un laberinto limpio

    for(;;)
    {
        uint8 orderToSend = 0;
        
        if (modeSelected == 1) {
            orderToSend = Exploration();
        }
        else if (modeSelected == 2) {
            orderToSend = FastMode();
        }
        else if (modeSelected == 3) {
            // TestRoutine()
            // El modo de prueba original enviaba 'L'. Lo mantenemos por ahora.
            orderToSend = codification('L');
            CyDelay(1000); // Delay para no enviar comandos constantemente
            // Desactivamos el modo para que solo se ejecute una vez por selección
            modeSelected = 0; 
        }
        
        // Enviar el comando solo si es válido (diferente de 0)
        if(orderToSend != 0){
            UART_1_WriteTxData(orderToSend);
            // Esperar un poco antes del siguiente movimiento.
            // Este delay es importante para dar tiempo al robot a moverse
            // y al ATmega a responder con los nuevos datos de los sensores.
            // Ajusta el valor según sea necesario.
            CyDelay(500); 
        }

    }
}

