/*
 * API_debounce.h
 *
 *  Created on: Mar 27, 2025
 *      Author: Gus
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "stm32f4xx_hal.h"

#include <stdint.h>
#include <stdbool.h>

#include "API_delay.h"
#include "API_uart.h"

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

typedef bool bool_t;

void debounceFSM_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de transición de estados y actualizar las salida

bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
