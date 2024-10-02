#include "stm32f411ceu6_I2C.h"

// SYSCLK: PLL = 100Mhz, Prescal at APB1 = 2; -> FrequencyAPB1_Peripheral = 100Mhz / 2 = 50Mhz;
// TPCLK1 = 1/50Mhz = 0,02uS;
// FM_FREQ (tSCL) = 1/400kHz = 2,5uS = 2500ns;
// If FM in tLow/tHigh = 16/9:
// tHigh + tLow = tSCL = 2500ns;
// -> 9 * CCR * 20ns + 16 * CCR * 20ns = 2500 ns -> CCR = 5;
// Maximum Tr = 300;
// 300ns / 20ns = 15ns; -> Trise = 15ns + 1 = 16ns;

void initI2C(I2C_Handle *I2C_Setup) {

	// ENABLE I2C CLOCK
	APB1_EN();

	// Disable I2C Peripheral First
	I2C_Setup->I2C->I2C_CR1 &= ~(1 << PERIPHERAL_EN_BIT);

	// *** SETTING CLOCK SPEED FOR I2C *** //
	// Set-up Frequency of I2C at 50MHZ
	I2C_Setup->I2C->I2C_CR2 |= (50 << FREQ_BIT);

	// Choose DUTY = 16/9
	I2C_Setup->I2C->I2C_CCR |= (1 << DUTY);

	// Choose FM I2c
	I2C_Setup->I2C->I2C_CCR |= (1 << FSM);

	// Select CCR to generate 400kHz (Fast Mode)
	I2C_Setup->I2C->I2C_CCR = (5 << CCR);

	// Set up TRISE
	I2C_Setup->I2C->I2C_TRISE |= (16 & 0x3F);
	// *** END OF SETTING CLOCK SPEED *** //

	// Setup Address
	I2C_Setup->I2C->I2C_OAR1 &= ~(1 << ADDRMODE);
	I2C_Setup->I2C->I2C_OAR1 |= (I2C_Setup->addrMode << ADDRMODE);

	// Address Dual
	I2C_Setup->I2C->I2C_OAR2 |= (I2C_Setup->addrDualEnable << ENDUAL);

	// OWN ADDRESS
	I2C_Setup->I2C->I2C_OAR1 |= (I2C_Setup->ownAddr << INTERFACE_ADDR);

	// Setup ACK
	I2C_Setup->I2C->I2C_CR1 &= ~(1 << ACK);
	I2C_Setup->I2C->I2C_CR1 |= (I2C_Setup->ENACK << ACK);

	// Setup Stretch Clock
	I2C_Setup->I2C->I2C_CR1 |= (I2C_Setup->stretchClock << NO_STRETCH);

	// Enable I2C
	I2C_Setup->I2C->I2C_CR1 |= (1 << PERIPHERAL_EN_BIT);
}



