#include <stdint.h>
#include "platform_init.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
    init_platform();
    uint8_t instruction = 0x0A;
    uint8_t datah, datal;

    while(true) {
      spi_startCommunication(SPI1_CS);
//      nop(10000);
      spi_transmitReceive(SPI1, &instruction, NULL, 1, false);
//      spi_transmitReceive(SPI1, NULL, &datal, 1, false);
//      nop(1000);
      spi_stopCommunication(SPI1_CS);
      nop(10000);
    }

}
