# Practica 5 - Uart

Este proyecto es un ejemplo básico de aplicación para microcontroladores STM32. Utiliza la HAL de STMicroelectronics para configurar el sistema, el reloj, los periféricos (GPIO y UART) y, además, implementa funciones de delay sin bloqueo para gestionar el parpadeo de un LED y el cambio de periodos mediante la interacción de un botón.

## Descripción

El firmware implementa las siguientes funcionalidades:

- **Configuración del sistema y periféricos:**  
  Inicializa el sistema, configura el reloj del microcontrolador, habilita los pines GPIO y configura el UART para comunicación serial.

- **Driver API para Delay sin Bloqueo:**  
  Se definen funciones para el manejo de delays sin utilizar retardos bloqueantes:
  - **delayInit:** Inicializa la estructura de delay, asignándole el tiempo actual, la duración especificada y marcándolo como inactivo.
  - **delayRead:** Evalúa si ha transcurrido el tiempo especificado. Si el delay no estaba iniciado, lo inicia; si ya estaba en ejecución, verifica si se cumplió la duración.
  - **delayWrite:** Permite modificar la duración del delay.
  - **delayStop:** Detiene el delay, configurándolo a 0 y marcándolo como no activo.
  - **delayIsRunning:** Verifica si el delay esta activo.
  
  - **API Debounce:**  
  Implementa la gestión del anti-rebote del botón utilizando una máquina de estados finitos (FSM).
  - **debounceFSM_init:** Inicializa la máquina de estados para gestionar el debounce del botón.
  - **debounceFSM_update:** Actualiza periódicamente la máquina de estados, validando la presión y liberación del botón con debounce.
  - **readKey:** Devuelve true si se ha detectado la pulsación del botón.

- **Control de LED y Cambio de Periodos:**  
  En el bucle principal, el LED (LD2) parpadea a intervalos definidos por un arreglo de periodos (`periods_array`). La pulsación del botón (B1) permite cambiar cíclicamente entre los diferentes periodos de parpadeo. Se utiliza un delay adicional para el anti-rebote del botón.

## Funcionamiento

- **Parpadeo del LED:**  
  El LED parpadea con un delay cuya duración se extrae de un arreglo de periodos (`periods_array`). Inicialmente se configura el primer periodo del arreglo.

- **Cambio de Periodo con Debounce:**  
  Al detectar una pulsación válida del botón gestionada por la FSM de debounce, se cambia cíclicamente el valor del periodo de delay, afectando el parpadeo del LED.
