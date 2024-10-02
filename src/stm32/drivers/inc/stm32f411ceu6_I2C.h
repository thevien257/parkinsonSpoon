#ifndef INC_STM32F411CEU6_I2C_H_
#define INC_STM32F411CEU6_I2C_H_
#include "stm32f411ceu6_generic.h"

// REG OAR1:
#define ADDRMODE 15
#define INTERFACE_ADDR 1

// REG CR1
#define ACK 10
#define NO_STRETCH 7

// REG OAR2
#define ENDUAL 0

// Reg RCC (IC1: 21, IC2: 22, IC3: 23)
#define I2CEN 21

// Reg I2C_CR1
#define PERIPHERAL_EN_BIT 0
#define STOP_GENERATION 9

// Reg I2C_CR2
#define FREQ_BIT 0
#define DUTY 14
#define FSM 15
#define CCR 0

// Reg I2C CR1
#define START 8
#define STOP 9

// Reg TRISE
#define TRISE_BIT 0

typedef struct {
	I2C_REG *I2C;
	uint8_t speedMode; // sm: 100khz, fm: 400khz
	uint8_t addrMode; // 7-bit or 10-bit
	uint8_t addrDualEnable; // If enable, Both OAR1 and OAR2 are recognized in 7-bit addressing mode
	uint8_t stretchClock; // This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until it is reset by software.
	uint8_t generalCall; // Enable or Disable?
	uint8_t ENACK; // Enable ACK
	uint16_t ownAddr; // The address
} I2C_Handle;

void initI2C(I2C_Handle *I2C_Setup);
//void I2CMasterSend(I2C_REG *I2C, uint8_t *pTXBuffer, uint32_t len,
//		uint8_t slaveADDr);

static inline void __attribute__((always_inline, section(".ramfunc"))) I2CMasterSend(
		I2C_REG *I2C, uint8_t *pTXBuffer, uint32_t len, uint8_t slaveADDr) {
	// Start condition
	I2C->I2C_CR1 |= (1 << START);
	// The SB bit is set by hardware, The master waits for a read of the SR1 register
	while (!(I2C->I2C_SR1 & (1)))
		;
	// Send Address
	slaveADDr = (slaveADDr << 1);
	slaveADDr &= ~(1); // RnW bit must be 0
	I2C->I2C_DR = slaveADDr;

	// Check for ADDR End of Sending Address
	while (!(I2C->I2C_SR1 & (1 << 1)))
		;

	// Clear ADDR bit by Reading SR1 first then SR2
	uint32_t clearADDR = I2C->I2C_SR1;
	clearADDR = I2C->I2C_SR2;
	(void) clearADDR;

	// Sending the data
	for (int i = 0; i < len; i++) {
		while (!(I2C->I2C_SR1 & 1))
			;
		I2C->I2C_DR = pTXBuffer[i];
	}

	// Wait for the hardware to Set the TxE and BTF
	while (!(I2C->I2C_SR2 & (1 << 7)))
		;
	while (!(I2C->I2C_SR2 & (1 << 2)))
		;

	// Stop Generation
	I2C->I2C_CR1 |= (1 << STOP_GENERATION);
}

static inline void __attribute__((always_inline, section(".ramfunc"))) I2CMasterReceive(
		uint8_t *pRXBuffer, I2C_REG *I2C, uint8_t slaveADDr, uint32_t len) {

	// Start condition
	I2C->I2C_CR1 |= (1 << START);
	// The SB bit is set by hardware, The master waits for a read of the SR1 register
	while (!(I2C->I2C_SR1 & (1)))
		;
	// Send Address
	slaveADDr = (slaveADDr << 1);
	slaveADDr |= (1); // RnW bit must be 1 to Read
	I2C->I2C_DR = slaveADDr;

	// Check for ADDR End of Sending Address
	while (!(I2C->I2C_SR1 & (1 << 1)))
		;

	if (len == 1) {

		// Disable ACK Bit before clear ADDR phase: because When the ADDR flag is cleared, the I²C peripheral immediately transitions to the data reception phase. The master is then prepared to receive data from the slave. If you don’t disable the ACK (i.e., prepare to send a NACK) before clearing the ADDR flag, the I²C peripheral assumes you are still in "ACK mode." This means that after receiving the first (and only) byte, it would send an ACK automatically, indicating that more data is expected, which is incorrect when you only want one byte.
		I2C->I2C_CR1 &= ~(1 << ACK);

		// Clear ADDR bit by Reading SR1 first then SR2
		uint32_t clearADDR = I2C->I2C_SR1;
		clearADDR = I2C->I2C_SR2;
		(void) clearADDR;

		// Wait until RxNE is SET
		while (!(I2C->I2C_SR1 & (1 << 6)))
			;

		// Generation Stop Condition
		I2C->I2C_CR1 |= (1 << STOP_GENERATION);

		// Read data From DR Register
		*pRXBuffer = I2C->I2C_DR;

	} else if (len > 1) {
		// Clear ADDR bit by Reading SR1 first then SR2
		uint32_t clearADDR = I2C->I2C_SR1;
		clearADDR = I2C->I2C_SR2;
		(void) clearADDR;

		for (int i = 0; i < len; i++) {
			// Wait until RxNE is SET
			while (!(I2C->I2C_SR1 & (1 << 6)))
				;

			// After the last second byte
			if (i == (len - 2)) {
				// Disable ACK bit
				I2C->I2C_CR1 &= ~(1 << ACK);

				// Generation Stop Condition
				I2C->I2C_CR1 |= (1 << STOP_GENERATION);
			}

			pRXBuffer[i] = I2C->I2C_DR;
		}
	}

}

#endif /* INC_STM32F411CEU6_I2C_H_ */
