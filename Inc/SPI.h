/*
 * SPI.h
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "stm32f1xx.h"

void enable_spi(SPI_TypeDef *SPIx);
uint8_t spi_transfer(SPI_TypeDef *SPIx, uint8_t data);

#endif /* SPI_H_ */
