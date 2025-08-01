/*
 * NRF24L01.h
 *
 */

#ifndef NRF24L01_H_
#define NRF24L01_H_

#include <stdint.h>
#include "stm32f1xx.h"

#define NRF_W_REGISTER     0x20
#define NRF_FLUSH_TX       0xE1
#define NRF_W_TX_PAYLOAD   0xA0
#define NRF_CSN_LOW()   (GPIOA->ODR &= ~(1 << 12))  // PA12 LOW
#define NRF_CSN_HIGH()  (GPIOA->ODR |= (1 << 12))   // PA12 HIGH
#define NRF_CE_LOW()    (GPIOA->ODR &= ~(1 << 11))  // PA11 LOW
#define NRF_CE_HIGH()   (GPIOA->ODR |= (1 << 11))   // PA11 HIGH

void nrf_write_register(uint8_t reg, uint8_t value);
void nrf_config();
uint8_t nrf_get_status();
uint8_t nrf_read_register(uint8_t reg);
uint8_t send_payload(uint8_t* data, uint8_t len);

#endif /* NRF24L01_H_ */
