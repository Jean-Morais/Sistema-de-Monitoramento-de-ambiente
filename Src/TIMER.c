/*
 * TIMER.c
 *
 */


#include "TIMER.h"
#include "stm32f1xx.h"

uint8_t delay_done1;

void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF){
		delay_done1 = 1;
		TIM2->SR &=~TIM_SR_UIF;
		TIM2->CR1 &= ~TIM_CR1_CEN;
	}
}

void enable_timer(){
	TIM2->PSC = 8000-1; 	//8000000/8000 =1000 i.e. 1ms
	TIM2->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM2_IRQn);

}

void delay_us(uint32_t millisec){
	delay_done1 = 0;
	TIM2->ARR = millisec - 1;
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM_CR1_CEN;
	while(!delay_done1);
	TIM2->PSC = 8-1;

}
