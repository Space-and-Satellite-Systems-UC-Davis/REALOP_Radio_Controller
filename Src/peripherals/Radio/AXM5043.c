// UHF (SPI1) will be on 433 MHz downlink
// VHF will be on 150 MHz uplink

#include "AXM5043.h"


void radio_init() {


}

void radio_spiWriteReg(void *address, uint8_t data) {
    uint8_t spiDATA[2];
    spiDATA[0] = (uint8_t) address & 0x7F; //Set MSB to 0
    spiDATA[1] = data;
    spi_startCommunication(UHF_SPI_CS);
    spi_transmitReceive(UHF_SPI, spiDATA, NULL, 2, false);
    spi_stopCommunication(UHF_SPI_CS);
}

