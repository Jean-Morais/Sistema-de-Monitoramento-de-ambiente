/*
 * I2C.h
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

//Inicializar funções
void I2C1_Init(void);
void I2C1_Start(void);
void I2C1_Stop(void);
int I2C1_Address(uint8_t addr);
void I2C1_Write(uint8_t data);
uint8_t I2C1_Read(uint8_t ack);

#endif /* I2C_H_ */
