/*
 * stm32f411ceu6_GPIO.h
 *
 *  Created on: Sep 14, 2024
 *      Author: ADMIN
 */

#ifndef INC_STM32F411CEU6_GPIO_H_
#define INC_STM32F411CEU6_GPIO_H_

#include "stm32f411ceu6_generic.h"

// GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR and GPIOx_PUPDR, ALT

//typedef struct {
//	uint8_t GPIO_PIN_NUMBER; // selectPinNumber
//	uint8_t GPIO_MODE; // INPUT or OUTPUT
//	uint8_t GPIO_OTYPER; // PUSH-PULL or OPEN-DRAIN
//	uint8_t GPIO_OSPEEDR; // The higher speed is, the more straight up Time Rise and Time Fall is
//	uint8_t GPIO_PUDR; // PULL-UP or PULL-DOWN
//	uint8_t GPIO_ALTFUNC; // Alternate FUNCTION
//} GPIO_InitConfig;

//GPIO_InitConfig GPIO_config;

// *** PIN NUMBER DEFINE *** //
#define B1 1
#define B0 0
#define B10 10
#define B0 0
#define A7 7
#define A6 6
#define A5 5
#define A4 4
#define A3 3
#define A2 2
#define A1 1
#define A0 0
#define C15 15
#define C14 14
#define C13 13
#define B12 12
#define B13 13
#define B14 14
#define B15 15
#define A8 8
#define A9 9
#define A10 10
#define A11 11
#define A12 12
#define A15 15
#define B3 3
#define B4 4
#define B5 5
#define B6 6
#define B7 7
#define B8 8
#define B9 9
// *** END ///

#define ERROR 12

//*** MODE ***//
#define INPUT 00
#define OUTPUT 01
#define ALTERNATE 10
#define ANALOG 11
//*** END ***//

//*** VAL ***//
#define LOW 0
#define HIGH 1
//*** END ***//

// *** SPEED ***//
#define LOW_SPEED 6
#define MEDIUM 7
#define FAST 8
#define HIGH_SPEED 3
//*** END ***//

// *** OUTPUT TYPE ***//
#define PUSHPULL 0
#define OPDRAIN 1
// *** END ***//

// *** PUPD ***//
#define NO_PUPD 00
#define PUL_UP 01
#define PULL_DOWN 10
#define RESERVED 11

typedef struct {
	GPIO_REG *pGPIO;
	uint8_t GPIO_PIN_NUMBER; // selectPinNumber
	uint8_t GPIO_MODE; // INPUT or OUTPUT
	uint8_t GPIO_OUTPUT_TYPE; // PUSH-PULL or OPEN-DRAIN
	uint8_t GPIO_OUTPUT_SPEED; // The higher speed is, the more straight up Time Rise and Time Fall is
	uint8_t GPIO_SET_PUPD; // PULL-UP or PULL-DOWN
	uint8_t GPIO_SET_ALTERNATE; // Alternate FUNCTION
} GPIO_HANDLE; // GPIO_PORT

// Declare function prototypes
void initGPIO(GPIO_HANDLE *gpioHandle);
uint8_t GPIO_read(GPIO_REG *pGPIO, uint8_t GPIO_PIN_NUMBER);
void GPIO_write(GPIO_REG *pGPIO, uint8_t GPIO_PIN_NUMBER, uint8_t outVal);
void GPIO_ClockControl(GPIO_REG *pGPIO);
#endif /* INC_STM32F411CEU6_GPIO_H_ */
