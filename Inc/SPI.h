/*
 * SPI.h
 *
 *  Created on: Jul 1, 2025
 *      Author: Jean Morais
 *      		Joao Pedro
 *      		Gabriel
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

//void spi_enable_clock();
void spi_enable_port();
void spi_config(SPI_TypeDef *SPIx);
uint8_t spi_transfer(SPI_TypeDef *SPIx, uint8_t data);
void spi_write_reg(SPI_TypeDef *SPIx, GPIO_TypeDef *GPIOx, uint16_t CS_Pin, uint8_t addr, uint8_t val);
uint8_t spi_read_reg(SPI_TypeDef *SPIx, GPIO_TypeDef *GPIOx, uint16_t CS_Pin, uint8_t addr);

#endif /* SPI_H_ */
