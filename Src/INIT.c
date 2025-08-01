/*
 * INIT.c
 *
 */


#include "INIT.h"
#include "stm32f1xx.h"
#include "TIMER.h"
#include "NRF24L01.h"


void enable_gpio(){

// SPI_1 mestre --------------------------------------------------------------

	//NSS
	GPIOA->CRL &= 0xFFF0FFFF; // limpa os bits do A4
	GPIOA->CRL |= 0x00020000; // habilita A4 como out push pull

	//SCK
	GPIOA->CRL &= 0xFF0FFFFF; // limpa os bits do A5
	GPIOA->CRL |= 0x00A00000; // habilita A5 como out AF push pull

	// MISO
	GPIOA->CRL &= 0xF0FFFFFF; // limpa os bits do A6
	GPIOA->CRL |= 0x04000000; // habilita A6 como input floating

	//MOSI
	GPIOA->CRL &= 0x0FFFFFFF; // limpa os bits do A7
	GPIOA->CRL |= 0xA0000000; // habilita A7 como out AF push pull

// USART ---------------------------------------------------------------------

	GPIOA->CRH &= ~(0xF << 4);     // Limpa bits de configuração de PA9
	GPIOA->CRH |= (0xB << 4);      // 1011 = AF output push-pull, 50 MHz

	// PA10 (RX) como input floating
	GPIOA->CRH &= ~(0xF << 8);     // Limpa bits de configuração de PA10
	GPIOA->CRH |= (0x4 << 8);      // 0100 = input floating

// NRF

	// CSN -> PA12
	GPIOA->CRH &= ~(0xF << 16);     // limpa bits de PA12
	GPIOA->CRH |= (0x2 << 16);      // Output push-pull

	// CE -> PA11
	GPIOA->CRH &= ~(0xF << 12);     // limpa bits de PA11
	GPIOA->CRH |= (0x2 << 12);      // Output push-pull


	NRF_CE_LOW();  // CE em LOW
	NRF_CSN_HIGH(); // CSN em HIGH (inativo)

// i2c

	GPIOB->CRL &= ~((0xF << 24) | (0xF << 28));
	GPIOB->CRL |=  (0xB << 24) | (0xB << 28);

// LED TESTE
	GPIOB->CRH &= 0xFFF0FFFF; // limpa os bits do B12
	GPIOB->CRH |= 0x00020000; // habilita A4 como out push pull

}

void enable_clock(){
	RCC->APB2ENR |= (1 << 2); //Enable GPIOA Clock A
	RCC->APB2ENR |= (1 << 3); //Enable GPIOC Clock B
	RCC->APB2ENR |= (1 << 4); //Enable GPIOC Clock C
	RCC->APB2ENR |= (1 << 12); //Enable Clock SPI_1
	RCC->APB2ENR |= (1 << 14); //Enable usart1
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //Enable ADC1 clock TO LDR
	RCC->CR |= RCC_CR_HSION; // Liga o HSI (já vem ligado por padrão)
	while (!(RCC->CR & RCC_CR_HSIRDY)); // Espera HSI estabilizar
	RCC->CFGR |= RCC_CFGR_SW_HSI;
}

void teste(){
	delay_us(100000);
	GPIOB->ODR |= B12;
	delay_us(500000);
	GPIOB->ODR &=~B12;
}
