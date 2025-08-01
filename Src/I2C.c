/*
 * I2C.c
 *
 */

#include "stm32f1xx.h"
#include "I2C.h"

void I2C1_Init(void) {
	RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
	I2C1->CR1 &= ~I2C_CR1_PE;
	I2C1->CR2 = 8;
	I2C1->CCR = 80;
	I2C1->TRISE = 9;
    I2C1->CR1 |= I2C_CR1_ACK;
    I2C1->CR2 |= I2C_CR2_LAST;
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_Start(void) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));
}

void I2C1_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
}

int I2C1_Address(uint8_t addr) {
    I2C1->DR = addr;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;
    return 1;
}

// Escreve um byte no barramento I2C
void I2C1_Write(uint8_t data) {
	while (!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = data;
	while (!(I2C1->SR1 & I2C_SR1_BTF));
}

// Lê um byte do barramento I2C
uint8_t I2C1_Read(uint8_t ack) {
    if (ack) {
        I2C1->CR1 |= I2C_CR1_ACK;
    } else {
        I2C1->CR1 &= ~I2C_CR1_ACK;
    }

    while (!(I2C1->SR1 & I2C_SR1_RXNE));

    return I2C1->DR;
}
