# Proyecto Micromouse

Este repositorio contiene el código fuente para un robot "Micromouse" autónomo diseñado para explorar y resolver laberintos. El proyecto se basa en una arquitectura de dos microcontroladores para separar la lógica de alto nivel de las tareas de control en tiempo real.

## Arquitectura del Sistema

El robot utiliza dos microcontroladores que se comunican a través de UART:

1.  **Microcontrolador Principal (El Cerebro):**
    *   **Dispositivo:** Cypress PSoC.
    *   **Responsabilidades:**
        *   Ejecutar el algoritmo de resolución de laberintos (Flood Fill).
        *   Tomar decisiones estratégicas sobre la ruta a seguir.
        *   Gestionar los modos de operación del robot.
        *   Enviar comandos de movimiento (avanzar, girar) al microcontrolador secundario.

2.  **Microcontrolador Secundario (La Fuerza):**
    *   **Dispositivo:** Atmel ATmega (programado en ensamblador).
    *   **Responsabilidades:**
        *   Controlar los motores DC mediante PWM.
        *   Implementar un **controlador PID** para una regulación precisa de la velocidad, utilizando la retroalimentación de los encoders de las ruedas.
        *   Leer los sensores de pared (infrarrojos) y enviar la información al PSoC.
        *   Ejecutar los comandos de movimiento básicos recibidos del PSoC.

## Hardware

*   **Chasis:** Estructura base del robot Micromouse.
*   **Microcontroladores:** 1x Cypress PSoC, 1x Atmel ATmega.
*   **Sensores:**
    *   3x Sensores de distancia infrarrojos (Izquierda, Frontal, Derecha) para la detección de paredes.
    *   2x Encoders en las ruedas para medir la distancia y velocidad.
*   **Actuadores:** 2x Motores DC.
*   **Interfaz de Usuario:**
    *   Botones para seleccionar el modo de operación.
    *   LEDs para indicar el estado actual.
    *   Display de 7 segmentos de 4 dígitos para mostrar información de depuración (posición, valor del flood, etc.).

## Software

### Lógica Principal (PSoC)

*   **Lenguaje:** C
*   **IDE:** Cypress PSoC Creator
*   **Algoritmo:** El robot utiliza el **algoritmo Flood Fill** para navegar. Este método le permite explorar el laberinto, mapear las paredes y, una vez explorado, calcular la ruta más corta hacia el centro.
*   **Modos de Operación:**
    1.  **Modo de Exploración:** El robot navega por el laberinto por primera vez, guardando la ubicación de las paredes en su memoria.
    2.  **Modo Rápido (Fast Mode):** Después de la exploración, el robot utiliza el mapa guardado para correr desde el inicio hasta el final por la ruta más corta y a la máxima velocidad posible.
    3.  **Modo de Prueba:** Permite verificar los movimientos básicos del robot.

### Control de Bajo Nivel (Atmel)

*   **Lenguaje:** Ensamblador (Assembly)
*   **IDE:** Atmel Studio (o Microchip Studio)
*   **Funcionalidad:** El código en ensamblador está altamente optimizado para tareas de tiempo real. Gestiona el PWM para los motores y ejecuta un bucle de control PID para asegurar que los movimientos (giros y avances) sean precisos y repetibles.

## Estructura del Repositorio

*   `./V13/`: Contiene el proyecto de PSoC Creator para la lógica principal y el algoritmo de resolución.
    *   Para abrir, usar `Proyecto.cywrk`.
*   `./ProyectoEmbebidos/`: Contiene el proyecto de Atmel Studio para el control de motores y sensores.
    *   Para abrir, usar `ProyectoEmbebidos.atsln`.

## Cómo Empezar

1.  **Clonar el repositorio:**
    ```bash
    git clone <URL-DEL-REPOSITORIO>
    ```
2.  **Abrir los proyectos:**
    *   Abrir el archivo `V13/Proyecto.cywrk` con **Cypress PSoC Creator**.
    *   Abrir el archivo `ProyectoEmbebidos/ProyectoEmbebidos.atsln` con **Atmel Studio** o **Microchip Studio**.
3.  **Compilar y Programar:**
    *   Compilar cada proyecto en su respectivo IDE.
    *   Programar el firmware resultante en cada uno de los microcontroladores.
