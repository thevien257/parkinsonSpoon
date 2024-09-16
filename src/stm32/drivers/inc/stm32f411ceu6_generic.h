#ifndef INC_STM32F411CEU6_GENERIC_H_
#define INC_STM32F411CEU6_GENERIC_H_

#include <stdint.h>

// ************** BUS ADDRESS ************** //
#define APB1_BASEADDR 0x40000000U
#define APB2_BASEADDR 0x40010000U
#define AHB1_BASEADDR 0x40020000U
#define AHB2_BASEADDR 0x50000000U
// ************** END ************** //

// ************** GPIO ADDRESS ************** //
// EXPLAIN: IN EACH BASEADDR HAS 32BIT REGISTERS WITH DIFFERENT ADDRESS
#define GPIOA_BASEADDR AHB1_BASEADDR
#define GPIOB_BASEADDR (0x40020400)
#define GPIOC_BASEADDR (0x40020800)
#define GPIOD_BASEADDR (0x40020C00)
#define GPIOE_BASEADDR (0x40021000)
#define GPIOH_BASEADDR (0x40021C00)
#define CRC_BASEADRR (0x40023000)
#define RCC_BASEADRR (0x40023800)
// ************** END ************** //

// ************** RCC CLOCK STRUCTURE ************** //
typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR; // RESET THE PERIPHERAL TO THE RESET VALUE
	volatile uint32_t AHB2RSTR; // RESET THE PERIPHERAL TO THE RESET VALUE
	uint32_t Reserved1[2];
	volatile uint32_t APB1RSTR; // RESET THE PERIPHERAL TO THE RESET VALUE
	volatile uint32_t APB2RSTR; // RESET THE PERIPHERAL TO THE RESET VALUE
	uint32_t Reserved2[2];
	volatile uint32_t AHB1ENR; // ENABLE CLOCK FOR THE FIRST TIME
	volatile uint32_t AHB2ENR; // ENABLE CLOCK FOR THE FIRST TIME
	uint32_t Reserved3[2];
	volatile uint32_t APB1ENR; // ENABLE CLOCK FOR THE FIRST TIME
	volatile uint32_t APB2ENR; // ENABLE CLOCK FOR THE FIRST TIME
	uint32_t Reserved4[2];
	volatile uint32_t AHB1LPENR; // LOW POWER MODE ENABLE CLOCK
	volatile uint32_t RCC_AHB2LPENR; // LOW POWER MODE ENABLE CLOCK
	uint32_t Reserved5[2];
	volatile uint32_t APB1LPENR; // LOW POWER MODE ENABLE CLOCK
	volatile uint32_t APB2LPENR; // LOW POWER MODE ENABLE CLOCK
	uint32_t Reserved6[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t Reserved7[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	uint32_t Reserved8;
	volatile uint32_t DCKCFGR;
} RCC_REG;
// ************** END ************** //

// ************** RCC POINTER DECLARE ************** //
// RCC_BASEADDR is just a number (an address), but to access the memory at that address, the compiler needs to know what type of data is stored there.
// By typecasting it to RCC_REG *, you tell the compiler that the memory at RCC_BASEADDR is organized according to the RCC_REG structure (cast it to the pointer of type struct).
// typecasts that address into a pointer to the RCC_REG struct.
// (RCC_REG *) is the typecast that tells the compiler: “I want to treat this address as if it is the starting address of a structure of type RCC_REG.”
#define RCC ((RCC_REG*)RCC_BASEADRR) // Similar to: RCC_REG* pRCC = (RCC_REG*)RCC_BASEADRR;
// ************** END ************** //

// ************** ENABLE CLOCK ************** //
#define GPIOA_CLK_EN() (RCC->AHB1ENR |= 1<<0)
#define GPIOB_CLK_EN() (RCC->AHB1ENR |= 1<<1)
#define GPIOB_CLK_LEN() (RCC->AHB1LPENR &= ~(1<<1))
#define GPIOC_CLK_EN() (RCC->AHB1ENR |= 1<<2)
#define GPIOD_CLK_EN() (RCC->AHB1ENR |= 1<<3)
#define GPIOE_CLK_EN() (RCC->AHB1ENR |= 1<<4)
#define GPIOH_CLK_EN() (RCC->AHB1ENR |= 1<<7)
// ************** END ************** //

// ************** STRUCT GPIO ************** //
typedef struct {
	volatile uint32_t GPIOx_MODER;
	volatile uint32_t GPIOx_OTYPER;
	volatile uint32_t GPIOx_OSPEEDR;
	volatile uint32_t GPIOx_PUPDR;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_LCKR;
	volatile uint32_t GPIOx_AFRL;
	volatile uint32_t GPIOx_AFRH;
} GPIO_REG;
// ************** END ************** //

// GPIO POINTER DECLARE
#define GPIOA (GPIO_REG*)GPIOA_BASEADDR
#define GPIOB (GPIO_REG*)GPIOB_BASEADDR
#define GPIOC (GPIO_REG*)GPIOC_BASEADDR
#define GPIOD (GPIO_REG*)GPIOD_BASEADDR
#define GPIOE (GPIO_REG*)GPIOE_BASEADDR
#define GPIOH (GPIO_REG*)GPIOH_BASEADDR
// ************** END ************** //

#include "stm32f411ceu6_GPIO.h"

#endif /* INC_STM32F411CEU6_GENERIC_H_ */
