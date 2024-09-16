/*
 * stm32f411ceu6_GPIO.c
 *
 *  Created on: Sep 15, 2024
 *      Author: ADMIN
 */

#include "stm32f411ceu6_GPIO.h"

void GPIO_ClockControl(GPIO_REG *pGPIOxReg) {

	if (pGPIOxReg == GPIOA) {
		GPIOA_CLK_EN();
	} else if (pGPIOxReg == GPIOB) {
		GPIOB_CLK_LEN();
		GPIOB_CLK_EN();
	} else if (pGPIOxReg == GPIOC) {
		GPIOC_CLK_EN();
	} else if (pGPIOxReg == GPIOD) {
		GPIOD_CLK_EN();
	} else if (pGPIOxReg == GPIOE) {
		GPIOE_CLK_EN();
	} else if (pGPIOxReg == GPIOH) {
		GPIOH_CLK_EN();
	}
}

void initGPIO(GPIO_HANDLE *gpioHandle) {
	// ENABLE CLOCK
	GPIO_ClockControl(gpioHandle->pGPIO);
	// INIT MODE
	gpioHandle->pGPIO->GPIOx_MODER &= ~(0x3 << 2 * gpioHandle->GPIO_PIN_NUMBER);
	gpioHandle->pGPIO->GPIOx_MODER |= (gpioHandle->GPIO_MODE
			<< 2 * gpioHandle->GPIO_PIN_NUMBER);
	gpioHandle->pGPIO->GPIOx_PUPDR &= ~(0x3 << 2 * gpioHandle->GPIO_PIN_NUMBER);
	gpioHandle->pGPIO->GPIOx_PUPDR |= (gpioHandle->GPIO_SET_PUPD
			<< 2 * gpioHandle->GPIO_PIN_NUMBER);
	if (gpioHandle->GPIO_MODE == OUTPUT) {
		gpioHandle->pGPIO->GPIOx_OTYPER &= ~(1 << gpioHandle->GPIO_PIN_NUMBER);
		gpioHandle->pGPIO->GPIOx_OTYPER |= (gpioHandle->GPIO_OUTPUT_TYPE
				<< gpioHandle->GPIO_PIN_NUMBER);
		gpioHandle->pGPIO->GPIOx_OSPEEDR &= ~(0x3
				<< 2 * gpioHandle->GPIO_PIN_NUMBER);
		gpioHandle->pGPIO->GPIOx_OSPEEDR |= (gpioHandle->GPIO_OUTPUT_SPEED
				<< 2 * gpioHandle->GPIO_PIN_NUMBER);
	}

}

uint8_t GPIO_read(GPIO_REG *pGPIO, uint8_t GPIO_PIN_NUMBER) {
// Implementation here
	return ((pGPIO->GPIOx_IDR >> GPIO_PIN_NUMBER) & 0x1);
}

void GPIO_write(GPIO_REG *pGPIO, uint8_t GPIO_PIN_NUMBER, uint8_t outVal) {
// Implementation here
	pGPIO->GPIOx_ODR = (pGPIO->GPIOx_ODR & ~(1 << GPIO_PIN_NUMBER))
			| ((outVal & 1) << GPIO_PIN_NUMBER);
}

