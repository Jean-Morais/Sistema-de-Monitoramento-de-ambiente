/*
 * USART.c
 *
 */

#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>

void enable_usart(){
	// Baud Rate: 9600 com HSI (8MHz) → USARTDIV ≈ 52.08 → 52.1 → 0x0201
	USART1->BRR = (52 << 4) | 1;
	USART1->CR1 = 0;
	USART1->CR1 |= (0 << 12);    // M = 0 (8 bits)
	USART1->CR2 &= ~(3 << 12);   // STOP = 00 (1 stop bit)
	USART1->CR1 |= (1 << 3);     // TE = 1 (habilita transmissor)
	USART1->CR1 |= (1 << 13);    // UE = 1 (USART enable)
}

void uart1_write_char(char c) {
    while (!(USART1->SR & (1 << 7))); // Espera TXE (transmit buffer empty)
    USART1->DR = c;
    while (!(USART1->SR & (1 << 6))); // Espera TC (transmission complete)
}

void uart1_write_string(const char *s) {
    while (*s) {
        uart1_write_char(*s++);
    }
}

void enviar_temp_press(int32_t temp, uint32_t press) {
    char buffer[64];

    // Converte valores para string (ex: "Temp: 2456, Press: 101325\r\n")
    sprintf(buffer, "Temp: %ld, Press: %lu\r\n", temp, press);

    // Envia via USART
    uart1_write_string(buffer);
}
