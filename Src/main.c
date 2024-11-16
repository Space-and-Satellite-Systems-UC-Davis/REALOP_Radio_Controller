#include <stdint.h>
#include "platform_init.h"
#include "Radio/AX5043.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
    init_platform();
    uint8_t instruction = 0x001;
    uint8_t datah, datal;

    while(true) {
    	blinky();
    	nop(100000);
    	radio_spiReadReg(0x01);
    }

}
