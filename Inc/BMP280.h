/*
 * BMP280.h
 *
 */

#ifndef BMP280_H_
#define BMP280_H_

#include <stdint.h>

// Registros do BMP280
#define BMP280_REG_CONTROL  0xF4
#define BMP280_REG_CONFIG   0xF5
#define BMP280_REG_TEMP_MSB 0xFA
#define BMP280_REG_PRESS_MSB 0xF7
#define BMP280_REG_CALIB    0x88
#define BMP280_ADDR        0x77

extern uint16_t dig_T1;
extern int16_t  dig_T2, dig_T3;
extern uint16_t dig_P1;
extern int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
extern int32_t  t_fine;

void BMP280_WriteReg(uint8_t reg, uint8_t value);
void BMP280_ReadRegMulti(uint8_t reg, uint8_t* buf, uint8_t len);
void BMP280_ReadCalibration(void);
void BMP280_Init(void);
int32_t BMP280_ReadTemperature(uint8_t* data);
uint32_t BMP280_ReadPressure(uint8_t* data);

#endif /* BMP280_H_ */
