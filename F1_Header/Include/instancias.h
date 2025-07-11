/*
 * instancias.h
 *
 *  Created on: Jun 29, 2025
 *      Author: jeanm
 */

#ifndef INSTANCIAS_H_
#define INSTANCIAS_H_

#include <stdint.h>
/*TIMER*/
void enable_timer();				/* Inicializar timer*/
void delay(uint32_t millisec);			/*delay em milisegundos*/

/*I2C*/
void    I2C1_Init(void);
void    I2C1_Start(void);
void    I2C1_Stop(void);
void    I2C1_SendAddress(uint8_t addr_rw);
void    I2C1_WriteByte(uint8_t data);
uint8_t I2C1_ReadByte_Ack(void);
uint8_t I2C1_ReadByte_Nack(void);


/*Sensor: AHT20*/
void    AHT20_Init(void);
uint8_t AHT20_ReadStatus(void);
void    AHT20_TriggerMeasurement(void);
void    AHT20_ReadRawData(uint8_t *data);
float   AHT20_ConvertHumidity(const uint8_t *data);
float   AHT20_ConvertTemperature(const uint8_t *data);


#endif /* INSTANCIAS_H_ */
