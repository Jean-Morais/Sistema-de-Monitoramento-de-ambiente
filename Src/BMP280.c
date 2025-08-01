/*
 * BMP280.c
 *
 */

#include <stdint.h>
#include "stm32f1xx.h"
#include "I2C.h"
#include "BMP280.h"

uint16_t dig_T1;
int16_t  dig_T2, dig_T3;
uint16_t dig_P1;
int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
int32_t  t_fine;

void BMP280_WriteReg(uint8_t reg, uint8_t value) {
    I2C1_Start();
    I2C1_Address(BMP280_ADDR << 1 | 0);
    I2C1_Write(reg);
    I2C1_Write(value);
    I2C1_Stop();
}

void BMP280_ReadRegMulti(uint8_t reg, uint8_t* buf, uint8_t len) {
    I2C1_Start();
    I2C1_Address(BMP280_ADDR << 1 | 0);
    I2C1_Write(reg);

    I2C1_Start();  // Repeated start
    I2C1_Address(BMP280_ADDR << 1 | 1);

    for (uint8_t i = 0; i < len; i++) {
        buf[i] = I2C1_Read(i < (len - 1));  // ACK until last
    }

    I2C1_Stop();
}

void BMP280_ReadCalibration(void) {
    uint8_t calib[24];
    BMP280_ReadRegMulti(BMP280_REG_CALIB, calib, 24);

    dig_T1 = (uint16_t)(calib[1] << 8 | calib[0]);
    dig_T2 = (int16_t)(calib[3] << 8 | calib[2]);
    dig_T3 = (int16_t)(calib[5] << 8 | calib[4]);
    dig_P1 = (uint16_t)(calib[7] << 8 | calib[6]);
    dig_P2 = (int16_t)(calib[9] << 8 | calib[8]);
    dig_P3 = (int16_t)(calib[11] << 8 | calib[10]);
    dig_P4 = (int16_t)(calib[13] << 8 | calib[12]);
    dig_P5 = (int16_t)(calib[15] << 8 | calib[14]);
    dig_P6 = (int16_t)(calib[17] << 8 | calib[16]);
    dig_P7 = (int16_t)(calib[19] << 8 | calib[18]);
    dig_P8 = (int16_t)(calib[21] << 8 | calib[20]);
    dig_P9 = (int16_t)(calib[23] << 8 | calib[22]);
}

void BMP280_Init(void) {
    BMP280_WriteReg(BMP280_REG_CONTROL, 0x27);  // temp & press oversampling x1, mode normal
    BMP280_WriteReg(BMP280_REG_CONFIG, 0xA0);   // Standby 1000ms, filter off
    BMP280_ReadCalibration();
}

int32_t BMP280_ReadTemperature(uint8_t* data) {
    BMP280_ReadRegMulti(BMP280_REG_TEMP_MSB, data, 3);

    int32_t adc_T = (int32_t)(((uint32_t)(data[0]) << 12) | ((uint32_t)(data[1]) << 4) | ((data[2] >> 4)));

    int32_t var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    int32_t var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;
    int32_t T = (t_fine * 5 + 128) >> 8;

    return T;  // Em décimos de grau Celsius (ex: 256 = 25.6°C)
}

uint32_t BMP280_ReadPressure(uint8_t* data) {
    BMP280_ReadRegMulti(BMP280_REG_PRESS_MSB, data, 3);

    int32_t adc_P = (((int32_t)(data[0]) << 12) | ((int32_t)(data[1]) << 4) | ((data[2] >> 4)));

    int64_t var1 = ((int64_t)t_fine) - 128000;
    int64_t var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

    if (var1 == 0) return 0;  // evita divisão por zero

    int64_t p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (uint32_t)(p >> 8);  // em Pa
}
