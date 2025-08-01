/*
 * SPI.c
 *
 */

#include <stdint.h>
#include "stm32f1xx.h"

void enable_spi(SPI_TypeDef *SPIx){
	SPIx->CR1 = 0; // limpa tudo
	SPIx->CR1 |= (2 << 3); // Define a taxa de transmissão do SCK fsk/8
	SPIx->CR1 &= ~((1 << 1) | (1 << 0));
	SPIx->CR1 &= ~(1 << 7);
	SPIx->CR1 |= (1 << 9); // Habilita NSS via software
	SPIx->CR1 |= (1 << 8); // Entrada do SSM
	SPIx->CR1 |= (1 << 2); // Mestre
	SPIx->CR1 |= (1 << 6); // Habilita SPI
}

uint8_t spi_transfer(SPI_TypeDef *SPIx, uint8_t data) {
	while (!(SPIx->SR & SPI_SR_TXE));   // Espera buffer de transmissão vazio
	SPIx->DR = data;                    // Envia o dado
	while (!(SPIx->SR & SPI_SR_RXNE));  // Espera dado recebido
	return SPIx->DR;                    // Retorna o dado recebido
}



