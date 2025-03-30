/*
 * API_debounce.c
 *
 *  Created on: Mar 27, 2025
 *      Author: Gus
 */

#include "API_debounce.h"

static debounceState_t current_state;
static delay_t delay_debounce;

static bool_t key = false;

GPIO_TypeDef * buttonPort;
uint16_t buttonPin;

/**
 * @brief Cambia el estado actual de la máquina de estados.
 * @param new_state Nuevo estado al cual se cambiará.
 */
static void setState(debounceState_t new_state)
{
	current_state = new_state;
}

/**
 * @brief Lee el estado actual del botón desde el puerto GPIO configurado.
 * @return Estado actual del pin GPIO (GPIO_PIN_SET o GPIO_PIN_RESET).
 */
static GPIO_PinState readButton()
{
	return HAL_GPIO_ReadPin(buttonPort, buttonPin);
}

/**
 * @brief Acción a realizar cuando el botón es presionado.
 */
static void buttonPressed()
{
	key = true;
}

/**
 * @brief Acción a realizar cuando el botón es liberado.
 *        (Actualmente no realiza ninguna acción.)
 */
static void buttonReleased()
{
	// No hace nada
}

/**
 * @brief Inicializa la máquina de estados para el debounce del botón.
 * @param GPIOx Puerto GPIO del botón.
 * @param GPIO_Pin Pin GPIO del botón.
 */
void debounceFSM_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	buttonPort = GPIOx;
	buttonPin = GPIO_Pin;
	current_state = BUTTON_DOWN;
	delayInit(&delay_debounce, 40);
}

/**
 * @brief Actualiza la máquina de estados para el debounce. Debe llamarse periódicamente.
 */
void debounceFSM_update()
{
	switch(current_state)
	{
		case BUTTON_UP:
		{
			if(readButton() == GPIO_PIN_SET)
			{
				setState(BUTTON_FALLING);
				delayRead(&delay_debounce);
			}
			break;
		}

		case BUTTON_FALLING:
		{
			if(delayRead(&delay_debounce))
			{
				if(readButton() == GPIO_PIN_SET)
				{
					setState(BUTTON_DOWN);
					buttonPressed();
				}
				else
				{
					setState(BUTTON_UP);
				}
			}
			break;
		}

		case BUTTON_DOWN:
		{
			if(readButton() == GPIO_PIN_RESET)
			{
				setState(BUTTON_RAISING);
				delayRead(&delay_debounce);
			}
			break;
		}

		case BUTTON_RAISING:
		{
			if(delayRead(&delay_debounce))
			{
				if(readButton() == GPIO_PIN_RESET)
				{
					setState(BUTTON_UP);
					buttonReleased();
				}
				else
				{
					setState(BUTTON_DOWN);
				}
			}
			break;
		}
	}
}

/**
 * @brief Lee el valor del flag que indica si el botón fue presionado.
 *        Luego de leer, restablece el flag.
 * @return true si el botón fue presionado, false en caso contrario.
 */
bool_t readKey()
{
	bool_t ret = key;
	if(key) key=!key;

	return ret;
}
