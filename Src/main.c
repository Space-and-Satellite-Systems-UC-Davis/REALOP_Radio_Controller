#include <stdint.h>
#include "platform_init.h"
#include "Radio/AX5043.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

bool test_radio_reads_simple();

int main(void)
{
    /* Loop forever */
    init_platform();


	radio_init();
	uint8_t arr[100];
	for(uint8_t i = 0; i<100; i++){
		arr[i]  =i;
	}
	radio_transmit(100, &arr);
    // while(true) {
    // 	blinky();
    // 	nop(1000);
    // 	bool success = test_radio_reads_simple();
    // }

}

bool test_radio_reads_simple() {
	uint32_t fails = 0;

	uint8_t retval = ax5043_read8(AX5043_SILICONREVISION);
	if (retval == 0b01010001) fails |= (1 << 0);

	retval = ax5043_read8(AX5043_SCRATCH);
	if (retval == 0b11000101) fails |= (1 << 1);

	ax5043_write8(AX5043_SCRATCH, 0xAA);

	retval = ax5043_read8(AX5043_SCRATCH);
	if (retval == 0xAA) fails |= (1 << 2);


	retval = ax5043_read8(AX5043_LPOSCREF0);
	if (retval == 0b10101000) fails |= (1 << 3);

	uint32_t wait = 33;

	return true;
}
