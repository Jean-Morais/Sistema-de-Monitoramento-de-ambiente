/*
 * SPI.c
 *
 *  Created on: Jul 1, 2025
 *      Author: Joao Pedro
 */

#include <stdint.h>
#include "stm32f1xx.h"

void spi_enable_clock(){

	RCC->APB2ENR |= (1 << 3); //Enable GPIOC Clock B
	RCC->APB1ENR |= (1 << 14); //Enable Clock SPI_2
}

void spi_enable_port(){
// SPI_2 mestre --------------------------------------------------------------
	spi_enable_clock();

	//NSS
	GPIOB->CRH &= 0xFFF0FFFF; // limpa os bits do B12
	GPIOB->CRH |= 0x00020000; // habilita B12 como out push pull

	//SCK
	GPIOB->CRH &= 0xFF0FFFFF; // limpa os bits do B13
	GPIOB->CRH |= 0x00A00000; // habilita B13 como out AF push pull

	// MISO
	GPIOB->CRH &= 0xF0FFFFFF; // limpa os bits do B14
	GPIOB->CRH |= 0x04000000; // habilita B14 como input floating

	//MOSI
	GPIOB->CRH &= 0x0FFFFFFF; // limpa os bits do B15
	GPIOB->CRH |= 0xA0000000; // habilita B15 como out AF push pull

	GPIOC->CRH &= ~(0xF << 28);   // limpa bits de configuração de PC15
	GPIOC->CRH |= (0x2 << 28);    // saída push-pull

	// Coloca PC15 em nível alto (libera o reset)
	GPIOC->ODR |= (1 << 15);
}

void spi_config(SPI_TypeDef *SPIx){

	SPIx->CR1 = 0; // limpa tudo
	SPIx->CR1 |= (2 << 3); // Define a taxa de transmissão do SCK fsk/8
	SPIx->CR1 &= ~((1 << 1) | (1 << 0));
	//SPI1->CR1 &= ~(1 << 11); // Formato de quadros = 8
	SPIx->CR1 &= ~(1 << 7);
	SPIx->CR1 |= (1 << 9); // Habilita NSS via software
	SPIx->CR1 |= (1 << 8); // Entrada do SSM
	SPIx->CR1 |= (1 << 2); // Mestre
	SPIx->CR1 |= (1 << 6); // Habilita SPI
}

uint8_t spi_transfer(SPI_TypeDef *SPIx, uint8_t data){

	while (!(SPIx->SR & SPI_SR_TXE));   // Espera buffer de transmissão vazio
	SPIx->DR = data;                    // Envia o dado
	while (!(SPIx->SR & SPI_SR_RXNE));  // Espera dado recebido
	return SPIx->DR;                    // Retorna o dado recebido
}

void spi_write_reg(SPI_TypeDef *SPIx, GPIO_TypeDef *GPIOx, uint16_t CS_Pin, uint8_t addr, uint8_t val){

	GPIOx->ODR &= ~CS_Pin;          // CS baixo (ativo)
	spi_transfer(SPIx, addr | 0x80);// bit 7 = 1 para escrita
	spi_transfer(SPIx, val);        // dado a escrever
	GPIOx->ODR |= CS_Pin;           // CS alto (inativo)
}

uint8_t spi_read_reg(SPI_TypeDef *SPIx, GPIO_TypeDef *GPIOx, uint16_t CS_Pin, uint8_t addr){

	uint8_t val;
	GPIOx->ODR &= ~CS_Pin;          // CS baixo
	spi_transfer(SPIx, addr & 0x7F);// bit 7 = 0 para leitura
	val = spi_transfer(SPIx, 0x00); // dummy write para ler dado
	GPIOx->ODR |= CS_Pin;           // CS alto
	return val;
}




