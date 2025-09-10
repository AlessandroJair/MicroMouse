.CSEG
RJMP start
.ORG 0x0006
RJMP PCINT0_I
.ORG 0x00A
RJMP PCINT2_I
.ORG 0x0012
RJMP overflow_handler1
start:
	;Configuración de las entradas y salidas
    LDI R16, 0b00111110
	OUT DDRB, R16
	LDI R16, 0x00
	OUT DDRC, R16
	LDI R16, 0b00001110
	OUT DDRD, R16
	;Inicializamos en vector de interrupciones
	LDI	R16,HIGH(RAMEND);Puntero de pila en el final de 
	OUT	SPH,R16	    ;la memoria SRAM
	LDI	R16,LOW(RAMEND)	
	OUT	SPL,R16
	;Configuración Reloj 2
	LDI R16, 0x04 ;Escala 64
	STS TCCR2B, R16
	;Configuración del PWM
	LDI R16, 0XA2 
	STS TCCR1A, R16 ;Se activa el PWM y se inicializa el modo Fast PWM
	LDI R16, 0X1C 
	STS TCCR1B, R16 ;Se continua con la inicialización del modo Fast PWM y el factor de preescalamiento es 256
	LDI R16, 0X03
	STS ICR1H, R16 ;Se carga el valor top como 1000
	LDI R16, 0XE8
	STS ICR1L, R16	
	;Configuración de la interrupcion PCINT0 y 2
	LDI R16, 0x05
	STS PCICR, R16
	;Colocamos el PWM en 0
	LDI R17, 0x00
	STS OCR1AH, R17
	LDI R18, 0x00
	STS OCR1AL, R18	
	STS OCR1BH, R17	
	STS OCR1BL, R18
	; Configuramos el UART
	;Tasa de Bits (Baudios: 9600) Velocidad doble
	LDI R16, 0x00
	STS UBRR0H, R16
	LDI R16, 0xCF
	STS UBRR0L, R16
	;Configuramos la comunicación en velocidad doble
	LDI R16, 0x22
	STS UCSR0A, R16
	; Modo asíncrono, Paridad: desactivada, 1 bit de parada, enviamos 8 bits
	LDI R16, 0x06
	STS UCSR0C, R16
	SEI
	LOOP:
		RCALL DETENER; Se detienen los motores
		;Activamos la transmisión y recepción
		CLR R28
		CLR R18; Mensaje a enviar
		;Se comparan las distancias medidas con la establecida
		SBIS PINC, 2
		ORI R18, 0b00000100; Hay un muro a la izquierda
		SBIS PINC, 1
		ORI R18, 0b00000010; Hay un muro al frente
		SBIS PINC, 0
		ORI R18, 0b00000001; Hay un muro a la derecha 
		CPI R18, 0x07
		BREQ MODI
		CONTINUAR_MODI:
		LDI R17, (1<<RXEN0)|(1<<TXEN0)
		STS UCSR0B, R17
		;Enviamos el mensaje
		RCALL PUT_TX
		RCALL GET_RX
		;R28 contiene el mensaje recibido
		;Controlamos la dirección de movimiento del robot
		SBRS R28, 5; Si no se activa en bit de inicio de la carrera no se mueve
		RJMP NO_MOVIMIENTO
		;Apagar UART
		LDI R17, 0x00
		STS UCSR0B, R17
		SBRC R28, 2
		RCALL VERI_IZQUIERDA;Si el tercer bit está en 1 se mueve a la izquierda
		SBRC R28, 0
		RCALL VERI_DERECHA;Si el priner bit está en 1 se mueve a la derecha
		SBRC R28, 1
		RCALL ADELANTE;Si el segundo bit está en 1 se mueve adelante
		SBRC R28, 3
		RCALL RETROCEDER;Si el cuarto bit está en 1 se mueve a la izquierda
		LDI R18, 0xFF
		RCALL PUT_TX
		RJMP LOOP
NO_MOVIMIENTO:	
	LDI R18, 0x0F
	RCALL PUT_TX
	RJMP LOOP	
PUT_TX:
	LDS R17, UCSR0A 
	SBRS R17, UDRE0
	RJMP PUT_TX

	STS UDR0, R18
	RET
GET_RX:
	LDS R17, UCSR0A
	SBRS R17, UDRE0
	RJMP GET_RX

	LDS R28, UDR0
	RET
MODI:
	LDI R18, 0x08
	RJMP CONTINUAR_MODI
VERI_IZQUIERDA:
	RCALL IZQUIERDA;Se realiza un giro de 90° a la izquierda
	SBRC R28, 4
	RCALL IZQUIERDA;Si el quinto bit está en 1 se realiza otro giro de 90°
	RET
VERI_DERECHA:
	RCALL DERECHA;Se realiza un giro de 90° a la derecha
	SBRC R28, 4
	RCALL DERECHA;Si el quinto bit está en 1 se realiza otro giro de 90°
	RET
DETENER:
	PUSH R28
	LDI R16, 0x00 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x00
	LDI R18, 0x00
	LDI R19, 0x00;Duty cycle 0%
	;Motor1
	STS OCR1AH, R18
	STS OCR1AL, R19
	;Motor2
	STS OCR1BH, R18
	STS OCR1BL, R19
	;Sentido de rotacion de motores
	OUT PORTB, R16
	OUT PORTD, R17
	POP R28
	RET
ADELANTE:
	PUSH R28
	LDI R16, 0x10 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x04
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0xFE ;Tiempo: 0.26s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	LDI R16, 0x10 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x04
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0xFE ;Tiempo: 0.26s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	POP R28
	RET
RETROCEDER:
	PUSH R28
	;Se retrocede el robot
	LDI R16, 0x08 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0xFE ;Tiempo: 0.26s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	;Se avanza nueve centimetros para centrar el robot
	LDI R16, 0x10 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x04
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0x56 ;Tiempo: 0.09s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	POP R28
	RET
DERECHA:
	PUSH R28
	LDI R16, 0x08;Rueda 1 y 2 giran en sentidos contrarios
	LDI R17, 0x04
	LDI R18, 0x03
	LDI R19, 0xA7;Duty cycle 93%
	LDI R23, 0xCD; 0.2s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	LDI R16, 0x08;Rueda 1 y 2 giran en sentidos contrarios
	LDI R17, 0x04
	LDI R18, 0x03
	LDI R19, 0xA7;Duty cycle 93%
	LDI R23, 0xCD; 0.2s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	LDI R16, 0x08;Rueda 1 y 2 giran en sentidos contrarios
	LDI R17, 0x04
	LDI R18, 0x03
	LDI R19, 0xA7;Duty cycle 93%
	LDI R23, 0xCD; 0.2s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	;Se retrocede el robot para alinealo correctamente
	LDI R16, 0x08 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0x26 ;Tiempo: 0.04s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	LDI R16, 0x08 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0x26 ;Tiempo: 0.04s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	POP R28
	RET
IZQUIERDA:
	PUSH R28
	LDI R16, 0x10;Rueda 1 y 2 giran en sentidos contrarios
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0xA7;Duty cycle 93%
	LDI R23, 0xCD; 0.2s
	LDI R20, 0x0F
	RCALL CONTROL_MOTORES
	LDI R16, 0x10;Rueda 1 y 2 giran en sentidos contrarios
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0xA7;Duty cycle 93%
	LDI R23, 0xCD; 0.2s
	LDI R20, 0x0F
	RCALL CONTROL_MOTORES
	LDI R16, 0x10;Rueda 1 y 2 giran en sentidos contrarios
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0xA7;Duty cycle 93%
	LDI R23, 0xCD; 0.2s
	LDI R20, 0x0F
	RCALL CONTROL_MOTORES
	;Se retrocede el robot para alinealo correctamente
	LDI R16, 0x08 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0x26 ;Tiempo: 0.04s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	;Se retrocede el robot para alinealo correctamente
	LDI R16, 0x08 ;Rueda 1 y 2 giran en el mismo senstido
	LDI R17, 0x08
	LDI R18, 0x03
	LDI R19, 0x38 ;Duty cycle 82.4%
	LDI R23, 0x26 ;Tiempo: 0.04s
	LDI R20, 0x0F ;Setpoint
	RCALL CONTROL_MOTORES
	POP R28
	RET
PCINT0_I:
	PUSH R28
	PUSH R29
	PUSH R18
	IN R29, SREG
	PUSH R29
	;Motor 1
	MOV R18, R24
	SWAP R18
	ANDI R24, 0x0F
	ANDI R18, 0xF0
	OR R24, R18
	SBIC PINB, 0
	ORI R24, 0x02 ;Enconder A (valor 1)
	SBIS PINB, 0
	ANDI R24, 0xFD ;Enconder A (valor 0)
	LDI YH, HIGH($200)
	LDI YL, LOW($200)
	;Conteo de pulsos
	;Motor1
	LD R18, Y ;Se utiliza R24 para registrar los movimientos
	CPI R18, 0x10;Sentido de giro antihorario
	BREQ SUB_RUT_IN0_2
	CPI R18, 0x08
	BREQ SUB_RUT_IN0_1 ;Sentido de giro horario
	CONT_INT_0:
	POP R29
	OUT SREG, R29
	POP R18
	POP R29	
	POP R28
	RETI
SUB_RUT_IN0_1:
	RCALL CONTEO_M1_1
	RJMP CONT_INT_0
SUB_RUT_IN0_2:
	RCALL CONTEO_M1_2
	RJMP CONT_INT_0
CONTEO_M1_1: 
	;Se evalua en el caso que nuestro motor 1 trabaje en sentido antihorario
	;Reduce el valor del conteo (horario)
	CPI R24, 0x20
	BREQ RESTA_M1_1
	CPI R24, 0x01
	BREQ RESTA_M1_1
	CPI R24, 0x32
	BREQ RESTA_M1_1
	CPI R24, 0x13
	BREQ RESTA_M1_1
	;Aumenta el valor del conteo (antihorario)
	CPI R24, 0x10
	BREQ SUMA_M1_1
	CPI R24, 0x31
	BREQ SUMA_M1_1
	CPI R24, 0x02
	BREQ SUMA_M1_1
	CPI R24, 0x23
	BREQ SUMA_M1_1
	FIN_CONTEO_M1_1:
	RET
SUMA_M1_1:
	INC R16
	RJMP FIN_CONTEO_M1_1
RESTA_M1_1:
	DEC R16
	RJMP FIN_CONTEO_M1_1
SUB_RUT_IN2_1:
	RCALL CONTEO_M1_1
	RJMP CONT_INT_2
SUB_RUT_IN2_2:
	RCALL CONTEO_M1_2
	RJMP CONT_INT_2
CONTEO_M1_2: 
	;Se evalua en el caso que nuestro motor 1 trabaje en sentido horario
	;Aumenta el valor del conteo (horario)
	CPI R24, 0x20
	BREQ SUMA_M1_2
	CPI R24, 0x01
	BREQ SUMA_M1_2
	CPI R24, 0x32
	BREQ SUMA_M1_2
	CPI R24, 0x13
	BREQ SUMA_M1_2
	;Reduce el valor del conteo (antihorario)
	CPI R24, 0x10
	BREQ RESTA_M1_2
	CPI R24, 0x31
	BREQ RESTA_M1_2
	CPI R24, 0x02
	BREQ RESTA_M1_2
	CPI R24, 0x23
	BREQ RESTA_M1_2
	RET
SUMA_M1_2:
	INC R16
	RJMP FIN_CONTEO_M1_1
RESTA_M1_2:
	DEC R16
	RJMP FIN_CONTEO_M1_1
PCINT2_I:
	PUSH R29
	PUSH R28
	PUSH R18
	IN R29, SREG
	PUSH R29
	LDI YH, HIGH($200)
	LDI YL, LOW($200)
	;Motor 1
	MOV R18, R24
	SWAP R18
	ANDI R24, 0x0F
	ANDI R18, 0xF0
	OR R24, R18
	SBIC PIND, 5
	ORI R24, 0x01 ;Enconder B (valor 1)
	SBIS PIND, 5
	ANDI R24, 0xFE ;Enconder B (valor 0)
	;Motor1 actualizacion de posicion
	LD R18, Y ;Se utiliza R24 para registrar los movimientos
	CPI R18, 0x10;Sentido de giro antihorario
	BREQ SUB_RUT_IN2_2
	CPI R18, 0x08
	BREQ SUB_RUT_IN2_1;Sentido de giro horario
	CONT_INT_2:
	;Motor 2
	MOV R18, R25
	SWAP R18
	ANDI R25, 0x0F
	ANDI R18, 0xF0
	OR R25, R18
	SBIC PIND, 6
	ORI R25, 0x02 ;Enconder A (valor 1)
	SBIS PIND, 6
	ANDI R25, 0xFD ;Enconder A (valor 0)
	SBIC PIND, 7
	ORI R25, 0x01 ;Enconder B (valor 1)
	SBIS PIND, 7
	ANDI R25, 0xFE ;Enconder B (valor 0)
	;Motor2
	INC YL
	LD R18, Y ;Se utiliza R25 para registrar los movimientos
	CPI R18, 0x04
	BREQ S_CONTEO_M2_2;Sentido de giro antihorario
	CPI R18, 0x08
	BREQ S_CONTEO_M2_1;Sentido de giro horario
	CONT_INT_2_1:
	POP R29
	OUT SREG, R29
	POP R18
	POP R28
	POP R29
	RETI
S_CONTEO_M2_1:
	RCALL CONTEO_M2_1
	RJMP CONT_INT_2_1
S_CONTEO_M2_2:
	RCALL CONTEO_M2_2
	RJMP CONT_INT_2_1
CONTEO_M2_1:
	;Se evalua en el caso que nuestro motor 2 trabaje en sentido horario
	;Aumenta el valor del conteo (horario)
	CPI R25, 0x20
	BREQ SUMA_M2_1
	CPI R25, 0x01
	BREQ SUMA_M2_1
	CPI R25, 0x32
	BREQ SUMA_M2_1
	CPI R25, 0x13
	BREQ SUMA_M2_1
	;Reduce el valor del conteo (antihorario)
	CPI R25, 0x10
	BREQ RESTA_M2_1
	CPI R25, 0x31
	BREQ RESTA_M2_1
	CPI R25, 0x02
	BREQ RESTA_M2_1
	CPI R25, 0x23
	BREQ RESTA_M2_1
	FIN_CONTEO_M2_1:
	RET
SUMA_M2_1:
	INC R17
	RJMP FIN_CONTEO_M2_1
RESTA_M2_1:
	DEC R17
	RJMP FIN_CONTEO_M2_1
CONTEO_M2_2:
	;Se evalua en el caso que nuestro motor 2 trabaje en sentido antihorario
	;Reduce el valor del conteo (horario)
	CPI R25, 0x20
	BREQ RESTA_M2_2
	CPI R25, 0x01
	BREQ RESTA_M2_2
	CPI R25, 0x32
	BREQ RESTA_M2_2
	CPI R25, 0x13
	BREQ RESTA_M2_2
	;Aumenta el valor del conteo (antihorario)
	CPI R25, 0x10
	BREQ SUMA_M2_2
	CPI R25, 0x31
	BREQ SUMA_M2_2
	CPI R25, 0x02
	BREQ SUMA_M2_2
	CPI R25, 0x23
	BREQ SUMA_M2_2
	FIN_CONTEO_M2_2:
	RET
SUMA_M2_2:
	INC R17
	RJMP FIN_CONTEO_M2_2
RESTA_M2_2:
	DEC R17
	RJMP FIN_CONTEO_M2_2
overflow_handler1: ;overflow interrupt handler routine
	PUSH R29
	IN R29, SREG
	PUSH R29
	INC R31
	POP R29
	OUT SREG, R29
	POP R29
	RETI
DIVIDIR:
	;Entradas: R18 (dividendo) y R29 (divisor)
	;Salida: R19 (cociente)
	PUSH R29
	CLR R19
	LOOP_DIVISION:
	CP R18, R29
	BRSH RESTA
	POP R29
	RET
RESTA:
	SUB R18, R29
	INC R19
	RJMP LOOP_DIVISION
PULSOS_MOTORES:
	;Motor1: R16 y Motor2:R17
	;R16 Y R17: Salida, indica la velocidad del motor en Pulsos
	;Escala: 64 (1s: 977)
	;Tiempo:100ms
	PUSH R29
	PUSH R23
	PUSH R22
	PUSH R24
	CLR R17
	CLR R16
	;Activamos las interrupciones con los pines PB0, PD5, PD6 y PD7
	LDI R19, 0x01
	STS PCMSK0,R30
	LDI R19, 0xE0
	STS PCMSK2,R30
	MOV R19, R31 ; Copiamos el valor del cronometro
	LDI R29, 0x62
	ADD R19, R29
	COUNT_PULSOS:
	CPI R16, 255
	BREQ MIN_R16
	CONTINUAR_CONTEO_3:
	CPI R17, 255
	BREQ MIN_R17
	CONTINUAR_CONTEO_4:
	CPI R16, 245
	BRSH OVER_R16
	CONTINUAR_CONTEO_1:
	CPI R17, 245
	BRSH OVER_R17
	CONTINUAR_CONTEO_2:
	CP R31, R23 ;Se verifica que no se haya excedido el valor requerido
	BRSH FIN_PID 
	;Se realiza un conteo durante 100ms
	CP R31, R19 ;Aproximadamente 100ms
	BRLO COUNT_PULSOS 
	;Desactivamos las interrupciones
	LDI R29, 0x00
	STS PCMSK0,R29
	STS PCMSK2,R29
	;Multiplicaciones para hallar las decimas de revolucion
	FIN_PROCESS:
	POP R24
	POP R22
	POP R23
	POP R29
	RET 
MIN_R16:
	LDI R16, 0x00
	RJMP CONTINUAR_CONTEO_3
MIN_R17:
	LDI R16, 0x00
	RJMP CONTINUAR_CONTEO_4
OVER_R16:
	LDI R16, 245
	RJMP CONTINUAR_CONTEO_1
OVER_R17:
	LDI R17, 245
	RJMP CONTINUAR_CONTEO_2
FIN_PID:
	;Desactivamos las interrupciones
	LDI R23, 0x00
	STS PCMSK0,R23
	STS PCMSK2,R23
	RJMP FIN_PROCESS
CONTROL_MOTORES:
	;Motor1:R18:R19 y Motor2:R20:21
	;VelocidadMotor1: R24, VelocidadMotor1: R25
	;Direccion motores Motor1: R16 y Motor2: R17
	;Velocidad de referencia R29
	;Tiempo: R23 (1s: 977)
	;Se configura según la velocidad deseada en cada motor
	;Motor1
	STS OCR1AH, R18
	STS OCR1AL, R19
	;Motor2
	STS OCR1BH, R18
	STS OCR1BL, R19
	;Inicializamos el vector
	LDI XH, HIGH($150)
	LDI XL, LOW($150)
	;Inicializamos los valores de errores e integrada de errores
	LDI R18, 0x00
	ST X, R18
	INC XL
	ST X, R18
	INC XL
	ST X, R18
	INC XL
	ST X, R18
	OUT PORTB, R16
	OUT PORTD, R17
	;Almacenamos la dirección de giro
	LDI YH, HIGH($200)
	LDI YL, LOW($200)
	ST Y, R16
	INC YL
	ST Y, R17
	LDI R16, 0x01 ;Se activa la bandera
	STS TIMSK2, R16
	CLR R31
	STS TCNT2, R31 ; Se reinicia el cronometro
	CLR R16
	CLR R17
	CLR R30
	CLR R24 ;Indicadores para los encoders
	CLR R25
	LOOP_MOTORES:
		;Se reinicia la cuenta del vector
		LDI XH, HIGH($150)
		LDI XL, LOW($150)
		LDI YH, HIGH($200)
		LDI YL, LOW($200)
		;Lectura de encoder
		RCALL PULSOS_MOTORES
		MOV R18, R17
		MOV R19, R20
		ANDI R30, 0x7F
		RCALL PID_V_MOTOR
		STS OCR1AH, R22
		STS OCR1AL, R21
		;Se controla la dirección de giro en caso de ser necesario
		LD R18, Y; Se lee el valor de direccion guardado
		SBRC R30,2
		RCALL INVERTIR_DIRECCION_MOTOR1		
		OUT PORTB, R18
		;Se implementa la nueva salida
		INC XL
		INC YL
		MOV R18, R17
		MOV R19, R20
		ORI R30, 0x80
		RCALL PID_V_MOTOR
		;Se implementa la nueva salida
		STS OCR1BH, R22
		STS OCR1BL, R21
		;Se controla la dirección de giro en caso de ser necesario
		LD R18, Y ;Se lee el valor guardado
		SBRC R30, 6
		RCALL INVERTIR_DIRECCION_MOTOR2
		OUT PORTD, R18
		CP R31, R23 ;Restricción de tiempo
		BRLO LOOP_MOTORES 
	FIN_PID_POS:
	RCALL DETENER
	;Desactivamos las interrupciones
	LDI R23, 0x00
	STS PCMSK0,R23
	STS PCMSK2,R23
	;Se reinicia la cuenta del vector
	LDI XH, HIGH($150)
	LDI XL, LOW($150)
	LDI YH, HIGH($150)
	LDI YL, LOW($150)
	CLR R16
	STS TIMSK2, R16;Desactivamos la bandera
	ST X, R16
	ST Y, R16
	INC YL
	ST Y, R16
	INC XL
	ST X, R16
	INC XL
	ST X, R16
	INC XL
	ST X, R16
	CLR R17
	CLR R27
	CLR R28
	CLR R22
	CLR R20
	CLR R21 
	CLR R25
	CLR R24
	RCALL Delay100ms;Delay de 100ms
	RET
INVERTIR_DIRECCION_MOTOR1:
	PUSH R23
	PUSH R29
	PUSH R28
	PUSH R27
	;Si es un valor esquecífico se utiliza el valor contrario
	CPI R18, 0x10
	BREQ INVERTIR_M1_P1
	;Si no es un valor esquecífico se utilizará este valor
	LDI R18, 0x10
	FIN_INVERSION_M1_P1:
	POP R27
	POP R28
	POP R29
	POP R23
	RET
INVERTIR_M1_P1:
	LDI R18, 0x08
	RJMP FIN_INVERSION_M1_P1
INVERTIR_DIRECCION_MOTOR2:
	PUSH R23
	PUSH R29
	PUSH R28
	PUSH R27
	;Si es un valor esquecífico se utiliza el valor contrario
	CPI R18, 0x08
	BREQ INVERTIR_M2_P1
	;Si no es un valor esquecífico se utilizará este valor
	LDI R18, 0x08
	FIN_INVERSION_M2_P1:
	POP R27
	POP R28
	POP R29
	POP R23
	RET
INVERTIR_M2_P1:
	LDI R18, 0x04
	RJMP FIN_INVERSION_M2_P1
PID_V_MOTOR:
	;Entradas: R18 (Revoluciones)
	;R19: Setpoint revolucones que debería tener
	;R21:R22 salida de PWM
	;R30:
	;0 y 4: (set) indican si el error es negativo
	;1 y 5: (set) indican si el valor guardado en la integral acumulada es negativa
	;2 y 6: (set) indican si la dirección de giro del motor se invierte
	;7: indica el motor con el que se opera
	PUSH R23
	PUSH R29
	PUSH R28
	PUSH R27
	LDI R28, 0x0A ;Kp (10/2)
	LDI R21, 0x02
	LDI R22, 0x0F ;Ki (15/10)
	RCALL ERROR_RUEDA
	;Calculamos P
	MUL R28, R19
	MOV R28, R0
	MOV R18,R28
	MOV R29, R21
	RCALL DIVIDIR
	MOV R28, R19
	;Integral de error
	LD R23, X
	ST X, R19
	ADD R23, R19
	CPI R23, 245
	BRSH OVER_I
	CONTINUAR_PID_I:
	;Leemos la integral calculada anteriormente
	INC XL
	LD R21, X
	RCALL OPERACION_INTEGRAL
	;Calculamos I
	MUL R23, R22
	MOV R23, R0
	LDI R29,0x0A;Ki
	MOV R18,R23
	RCALL DIVIDIR
	MOV R23, R19
	;Verificamos si se tienen que invertir los motores
	RCALL INVERSION_MOTOR
	;Convertirmos el valor a un PWM
	LDI R21, 0x0A
	MUL R28, R21
	MOV R18, R0
	LDI R29, 0x05
	RCALL DIVIDIR
	MOV R28,R19
	LDI R21, 0x64
	MUL R28, R21
	MOV R21, R0
	MOV R22, R1
	RCALL SATURACION
	POP R27
	POP R28
	POP R29
	POP R23
	RET
OVER_I:	
	LDI R23, 245
	RJMP CONTINUAR_PID_I
ERROR_RUEDA:
	;Si R19 es menor a R18 el error calculado será negativo
	CP R19,R18
	BRLO MINUS_ERROR
	SUB R19, R18;Cálculamos el error
	;Si el error es positivo se debe de desactivar el bit 1 o 4
	SBRC R30, 7
	RJMP INVERTIR_1
	;Si trabajamos con el motor 1 desactivamos en bit 0 de R30
	ANDI R30,0xFE
	RJMP FIN_ERROR
	INVERTIR_1:
	;Si trabajamos con el motor 1 desactivamos en bit 4 de R30
	ANDI R30,0xEF
	FIN_ERROR:
	RET
MINUS_ERROR:
	SUB R18, R19
	MOV R19, R18
	SBRC R30, 7
	RJMP INVERTIR_2
	;Si estamos trabajando con el motor 1 activamos el bit 0 de R30
	ORI R30,0x01
	;Cálculamos el error
	RJMP FIN_ERROR
	INVERTIR_2:
	;Si estamos trabajando con el motor 2 activamos el bit 4 de R30
	ORI R30,0x10
	RJMP FIN_ERROR
OPERACION_INTEGRAL:
	;Operaciones con la integral positiva
	;Verificamos si estamos trabajando con integrales negativas
	SBRC R30, 7
	RJMP OPERACION_INTEGRAL_M2
	SBRS R30, 7
	RJMP OPERACION_INTEGRAL_M1
	CONTINUAR_INT:
	ST X, R23
	RET
OPERACION_INTEGRAL_M1:
	;Operaciones con la integral negativa
	SBRC R30, 1
	RJMP INTEGRAL_NEGATIVA
	;Operaciones con la integral positiva
	SBRS R30, 1
	RJMP INTEGRAL_POSITIVA
OPERACION_INTEGRAL_M2:
	;Operaciones con la integral negativa
	SBRC R30, 5
	RJMP INTEGRAL_NEGATIVA
	;Operaciones con la integral positiva
	SBRS R30, 5
	RJMP INTEGRAL_POSITIVA
INTEGRAL_NEGATIVA:
	;Se verifica si estamos trabajando con el motor 1 o 2
	SBRS R30, 7
	RJMP INTEGRAL_MOTOR1_N
	SBRC R30, 7
	RJMP INTEGRAL_MOTOR2_N
INTEGRAL_MOTOR1_N:
	;En el motor 1, verificamos si nuestro error es negativo o positivo
	SBRC R30, 0
	RJMP RESTA_INTEGRAL_N ;Error negativo
	SBRS R30, 0
	RJMP SUMA_INTEGRAL_N ;Error positivo
INTEGRAL_MOTOR2_N:
	;En el motor 2, verificamos si nuestro error es negativo o positivo
	SBRC R30, 4
	RJMP RESTA_INTEGRAL_N ;Error negativo
	SBRS R30, 4
	RJMP SUMA_INTEGRAL_N;Error positivo
RESTA_INTEGRAL_N:
	ADD R23, R21 ;En la resta negativa R23 (integral actual), R21 (integral acumulada) se suma
	RJMP CONTINUAR_INT
SUMA_INTEGRAL_N:
	CP R21,R23 ;Si la integral acumulada es menor a la integral actual, entonces se pasará a un valor de positivo
	BRLO INT_INVERTIDA_N
	SUB R21, R23 ;En la suma negativa R23 (integral actual), R21 (integral acumulada) se restan
	MOV R23, R21
	RJMP CONTINUAR_INT
INT_INVERTIDA_N:
	;Subrutina para los dos motores
	;En caso se pase de negativo a positivo se escribe '0' en los bits 1 o 5 del R30
	SUB R23, R21 ;En la suma negativa R23 (integral actual), R21 (integral acumulada) se restan
	SBRS R30, 7
	ANDI R30, 0xFD
	SBRC R30, 7
	ANDI R30, 0xDF
	RJMP CONTINUAR_INT
INTEGRAL_POSITIVA:
	;Se verifica si estamos trabajando con el motor 1 o 2
	SBRS R30, 7
	RJMP INTEGRAL_MOTOR1
	SBRC R30, 7
	RJMP INTEGRAL_MOTOR2
INTEGRAL_MOTOR1:
	;En el motor 1, verificamos si nuestro error es negativo o positivo
	SBRC R30, 0
	RJMP RESTA_INTEGRAL;Error negativo
	SBRS R30, 0
	RJMP SUMA_INTEGRAL;Error positivo
INTEGRAL_MOTOR2:
	;En el motor 2, verificamos si nuestro error es negativo o positivo
	SBRC R30, 4
	RJMP RESTA_INTEGRAL;Error negativo
	SBRS R30, 4
	RJMP SUMA_INTEGRAL;Error positivo
RESTA_INTEGRAL:
	CP R21,R23 ;Si R21 es menor a R23, se pasará a números negativos
	BRLO INT_INVERTIDA
	SUB R21, R23 ;En la resta se trabaja con R23 (integral actual), R21 (integral acumulada)
	MOV R23, R21
	RJMP CONTINUAR_INT
INT_INVERTIDA:
	;Subrutina para los dos motores
	;En caso se pase de negativo a positivo se escribe '1' en los bits 1 o 5 del R30
	SUB R23, R21 ;En la resta se trabaja con R23 (integral actual), R21 (integral acumulada)
	SBRS R30, 7
	ORI R30, 0x02
	SBRC R30, 7
	ORI R30, 0x20
	RJMP CONTINUAR_INT
SUMA_INTEGRAL:
	ADD R23, R21 ;En la suma se trabaja con R23 (integral actual), R21 (integral acumulada) 
	RJMP CONTINUAR_INT
INVERSION_MOTOR:
	;Verificamos con que motor estamos trabajando
	SBRC R30, 7
	RJMP SECCION_M2
	SBRS R30, 7
	RJMP SECCION_M1
	CONTINUA_INV_M:
	RET
SECCION_M1:
	;Se verifica si la integración es negativa o positiva
	SBRC R30, 1
	RJMP MOTOR_1_INT_NEG ;Integración negativa
	SBRS R30, 1
	RJMP MOTOR_1_INT_POS;Integración positiva
	RJMP CONTINUA_INV_M
MOTOR_1_INT_POS: ;Integración positiva (I: positiva)
	SBRC R30, 0 ;Se verifica si P es negativo
	RJMP MOTOR_1_INV_1_P_NEG
	SBRS R30, 0 ;Se verifica si P es positivo
	RJMP MOTOR_1_INV_1_P_POS
	RJMP CONTINUA_INV_M
MOTOR_1_INV_1_P_POS:; (I: positiva) (P:positiva)
	ANDI R30, 0xFB ; Se escribe '0' en el bit 2 de R30
	ADD R28, R23 ;Calculamos el valor final de la entrada
	RJMP CONTINUA_INV_M
MOTOR_1_INV_1_P_NEG:; (I: positiva) (P:negativa)
	CP R28, R23 ; R23(I), R28(P), Integral negativa
	BRLO VERIFICACION_INV_M1
	ORI R30, 0X04 ;Se escribe '1' en el bit 2 de R30
	SUB R28, R23
	RJMP CONTINUA_INV_M
VERIFICACION_INV_M1:
	ANDI R30, 0xFB; Se escribe '0' en el bit 2 de R30
	SUB R23, R28;Calculamos el valor final de la entrada
	MOV R28, R23
	RJMP CONTINUA_INV_M
MOTOR_1_INT_NEG: ;Integral negativa (I: negativo)
	SBRC R30, 0 ;Se verifica si P es negativo
	RJMP MOTOR_1_INV_1_P_NEG_1
	SBRS R30, 0 ;Se verifica si P es positivo
	RJMP MOTOR_1_INV_1_P_POS_1
	RJMP CONTINUA_INV_M
MOTOR_1_INV_1_P_NEG_1:;(I: negativo) (P:negativo)
	ORI R30, 0x04; Se activa el bit 2 de R30
	ADD R28, R23 ;Calculamos el valor final de la entrada
	RJMP CONTINUA_INV_M
MOTOR_1_INV_1_P_POS_1:; (I: negativo) (P:positivo)
	CP R28, R23 ; R23(I), R28(P), Integral negativa
	BRLO VERIFICACION_INV_M1_NEG
	ANDI R30, 0xFB ;Se escribe '0' en el bit 2 de R30
	SUB R28, R23
	RJMP CONTINUA_INV_M
VERIFICACION_INV_M1_NEG:
	ORI R30, 0x04; Se escribe '1' en el bit 2 de R30
	SUB R23, R28;Calculamos el valor final de la entrada
	MOV R28, R23
	RJMP CONTINUA_INV_M
SECCION_M2:
	;Se verifica si el error es negativo o la integración es negativa
	SBRC R30, 5
	RJMP MOTOR_2_INT_NEG ;Integración negativa
	SBRS R30, 5
	RJMP MOTOR_2_INT_POS;Integración positiva
	RJMP CONTINUA_INV_M
MOTOR_2_INT_NEG:;Integral negativa (I: negativo)
	SBRC R30, 4 ;Se verifica si P es negativo
	RJMP MOTOR_2_INV_1_P_NEG_1
	SBRS R30, 4 ;Se verifica si P es positivo
	RJMP MOTOR_2_INV_1_P_POS_1
	RJMP CONTINUA_INV_M
MOTOR_2_INV_1_P_NEG_1:;(I: negativo) (P:negativo)
	ORI R30, 0x40; Se activa el bit 6 de R30
	ADD R28, R23 ;Calculamos el valor final de la entrada
	RJMP CONTINUA_INV_M
MOTOR_2_INV_1_P_POS_1:;(I: negativo) (P:positivo)
	CP R28, R23 ; R23(I), R28(P), Integral negativa
	BRLO VERIFICACION_INV_M2_NEG
	ANDI R30, 0xBF ;Se escribe '0' en el bit 6 de R30
	SUB R28, R23
	RJMP CONTINUA_INV_M
VERIFICACION_INV_M2_NEG:
	ORI R30, 0x40; Se escribe '1' en el bit 6 de R30
	SUB R23, R28;Calculamos el valor final de la entrada
	MOV R28, R23
	RJMP CONTINUA_INV_M
MOTOR_2_INT_POS:;Integración positiva (I: positiva)
	SBRC R30, 4 ;Se verifica si P es negativo
	RJMP MOTOR_2_INV_1_P_NEG
	SBRS R30, 4;Se verifica si P es positivo
	RJMP MOTOR_2_INV_1_P_POS
	RJMP CONTINUA_INV_M
MOTOR_2_INV_1_P_POS:; (I: positiva) (P:positiva)
	ANDI R30, 0xBF ; Se escribe '0' en el bit 6 de R30
	ADD R28, R23 ;Calculamos el valor final de la entrada
	RJMP CONTINUA_INV_M
MOTOR_2_INV_1_P_NEG:; (I: positiva) (P:negativa)
	CP R28, R23 ; R23(I), R28(P), Integral negativa
	BRLO VERIFICACION_INV_M2
	ORI R30, 0X40 ;Se escribe '1' en el bit 6 de R30
	SUB R28, R23
	RJMP CONTINUA_INV_M
VERIFICACION_INV_M2:
	ANDI R30, 0xBF; Se escribe '0' en el bit 2 de R30
	SUB R23, R28;Calculamos el valor final de la entrada
	MOV R28, R23
	RJMP CONTINUA_INV_M
SATURACION:
	CPI R22,0x03;Se evalua si el PWM supera el 100% (1000)
	BRLO FIN_SATURACION
	CPI R21,0xE8
	BRLO FIN_SATURACION
	LDI R21,0xE8
	LDI R22,0x03
FIN_SATURACION:
	RET
Delay100ms:
	PUSH R27
	PUSH R28
	PUSH R29
	ldi  r27, 9
    ldi  r28, 30
    ldi  r29, 229
L1: dec  r29
    brne L1
    dec  r28
    brne L1
    dec  r27
    brne L1
    nop
	POP R29
	POP R28
	POP R27
	RET