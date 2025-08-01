/*
 * TIMER.h
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

extern uint8_t delay_done1;

void TIM2_IRQHandler(void);
void enable_timer();
void delay_us(uint32_t millisec);

#endif /* TIMER_H_ */
