/*
 * LDR.c
 *
 */

#include "stm32f1xx.h"
#include "LDR.h"

//funcções referente ao ldr
void enable_LDR(){
	//config do ADC1
	ADC1->CR2 |= (7UL << ADC_CR2_EXTSEL_Pos);
	ADC1->CR2 |= (ADC_CR2_ADON);
}

void LDR_read(uint32_t *ldr_Data){
	//Reset ADC
	ADC1->CR2 |= ADC_CR2_ADON;
	//Iniciar conversão do ADC
	ADC1->CR2 |= ADC_CR2_SWSTART;

	//Esperar pelo EOC
	while(!(ADC1->SR & ADC_SR_EOC));

	*ldr_Data = ADC1->DR;
}

