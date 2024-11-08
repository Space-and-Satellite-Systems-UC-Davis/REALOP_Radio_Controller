#include "globals.h"
#include "stm32l431xx.h"
#include <SPI/spi.h>


#define UHF_SPI_CS SPI1_CS
#define UHF_SPI SPI1

void radio_init();

void radio_spiWriteReg(void *address, uint8_t data);