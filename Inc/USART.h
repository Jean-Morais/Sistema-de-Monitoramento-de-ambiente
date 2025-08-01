/*
 * USART.h
 *
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include "stm32f1xx.h"

void enable_usart();
void uart1_write_char(char c);
void uart1_write_string(const char *s);
void enviar_temp_press(int32_t temp, uint32_t press);

#endif /* USART_H_ */
