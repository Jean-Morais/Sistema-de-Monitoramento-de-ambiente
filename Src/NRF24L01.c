/*
 * NRF24L01.c
 *
 */


#include <stdio.h>
#include "NRF24L01.h"
#include "stm32f1xx.h"
#include "SPI.h"
#include "TIMER.h"
#include "INIT.h"
#include "USART.h"

void nrf_write_register(uint8_t reg, uint8_t value) {
    NRF_CSN_LOW();
    spi_transfer(SPI1, 0x20 | (reg & 0x1F)); // Comando de escrita
    spi_transfer(SPI1, value);              // Valor a ser escrito
    NRF_CSN_HIGH();
}

void nrf_config(){

	 nrf_write_register(0x01, 0x00); // habilita En_AA
	 nrf_write_register(0x02, 0x01); // habilita
	 nrf_write_register(0x03, 0x03); // endereço 5 bytes
	 nrf_write_register(0x04, 0xFF); // 250uS 2 retransmissoes
	 nrf_write_register(0x05, 0x0A); // canal 10
	 nrf_write_register(0x06, 0x0E); // RF

	 uint8_t addr[5] = {0x03, 0xDD, 0xCC, 0xBB, 0xAA};

	 NRF_CSN_LOW();
	 spi_transfer(SPI1, 0x30); // TX_ADDR
	 for(int i = 0; i < 5; i++) spi_transfer(SPI1, addr[i]);
	 NRF_CSN_HIGH();

	 NRF_CSN_LOW();
	 spi_transfer(SPI1, 0x0A); // RX_ADDR_P0 (receptor deve escutar neste)
	 for(int i = 0; i < 5; i++) spi_transfer(SPI1, addr[i]);
	 NRF_CSN_HIGH();


	 nrf_write_register(0x00, 0x02); // PWR_UP=1, PRIM_RX=0
	 delay_us(1500); // Esperar estabilização após PWR_UP
}

uint8_t nrf_get_status() {
    NRF_CSN_LOW();
    uint8_t status = spi_transfer(SPI1, 0xFF); // NOP = 0xFF → retorna STATUS
    NRF_CSN_HIGH();
    return status;
}

void nrf_write_command(uint8_t cmd) {
    NRF_CSN_LOW();
    spi_transfer(SPI1, cmd);
    NRF_CSN_HIGH();
}

uint8_t nrf_read_register(uint8_t reg) {
    NRF_CSN_LOW();
    spi_transfer(SPI1, 0x00 | (reg & 0x1F));  // comando de leitura do registrador
    uint8_t value = spi_transfer(SPI1, 0xFF); // leitura dummy
    NRF_CSN_HIGH();
    return value;
}

uint8_t send_payload(uint8_t* data, uint8_t len) {
    // FLUSH TX
    NRF_CSN_LOW();
    spi_transfer(SPI1, 0xE1); // FLUSH_TX
    NRF_CSN_HIGH();

    // Escreve payload no FIFO de TX
    NRF_CSN_LOW();
    spi_transfer(SPI1, 0xA0); // W_TX_PAYLOAD
    for (uint8_t i = 0; i < len; i++) {
        spi_transfer(SPI1, data[i]);
    }
    NRF_CSN_HIGH();

    // Pulso em CE para iniciar transmissão
    NRF_CE_HIGH();
    delay_us(15); // CE > 10us
    NRF_CE_LOW();

    // Aguarda transmissão completar
    while (!(nrf_read_register(0x07) & ((1 << 5) | (1 << 4)))) {
        // Espera até TX_DS ou MAX_RT
    }

    uint8_t status = nrf_read_register(0x07);

    if (status & (1 << 5)) {
        // Sucesso: limpa flag TX_DS
    	teste();
        nrf_write_register(0x07, 0x0E);
        return 1;
    } else if (status & (1 << 4)) {
        // Erro: MAX_RT atingido
        nrf_write_register(0x07, 0x0E); // limpa fla
        return 0;
    }

    return 0;
}

