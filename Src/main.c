/**
 ******************************************************************************
 * main
 */


#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"
#include "INIT.h"
#include "I2C.h"
#include "SPI.h"
#include "BMP280.h"
#include "NRF24L01.h"
#include "LDR.h"
#include "TIMER.h"
#include "USART.h"


int main(void) {
	enable_clock();
	enable_timer();
	enable_gpio();
	enable_spi(SPI1);
	I2C1_Init();
	enable_LDR();
	enable_usart();
	nrf_config();  // configuração básica
	BMP280_Init();
	uint32_t photo;
	uint8_t temp[3];
	uint8_t payload[6];
	uint32_t temperatura;
	char buffer1[20];
	char buffer2[20];
//
	while(1){
		delay_us(5000); // 1 segundo
		temperatura = BMP280_ReadTemperature(temp);
		LDR_read(&photo);
		sprintf(buffer1, "%lu\r\n", photo); // converte uint32_t para string com quebra de linha
		sprintf(buffer2, "%lu\r\n", temperatura);
		uart1_write_string("photo Sensor \r\n");
		uart1_write_string(buffer1);
		uart1_write_string("Temperatura \r\n");
		uart1_write_string(buffer2);
		payload[0] = temp[0];
		payload[1] = temp[1];
		payload[2] = temp[2];
		payload[3] = (uint8_t)(photo & 0xFF);
		payload[4] = (uint8_t)((photo >> 8) & 0xFF);
		payload[5] = (uint8_t)((photo >> 16) & 0xFF);
		send_payload(payload, 6); // envia 2 bytes
	}
}




