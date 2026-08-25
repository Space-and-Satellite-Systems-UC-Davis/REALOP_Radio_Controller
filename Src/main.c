#include <stdint.h>
#include "platform_init.h"
#include "Radio/AX5043.h"
#include <TestDefinition.h>
#include <globals.h>
#include "Sleep/sleep.h"
#include <Flight_Computer/Intercomm.h>

#define RUN_TEST	0	// 0 = run, 1 = run a very specific test
#define TEST_ID 	0	// ID of the test to run in case RUN_TEST = 1

volatile uint8_t interruptFlags = 0;


bool test_radio_reads_simple();

int main(void)
{
    /* Loop forever */
	init_platform();

	#if (RUN_TEST==1) && (TEST_ID != 0)

    void (*testFunc)();
    testFunc = getTestFunction(TEST_ID);
    testFunc();

    #else

	while (1) {
		while(interruptFlags){
			if(interruptFlags & RX_RECEIVED){
				NVIC_DisableIRQ(USART1_IRQn);
				interruptFlags &= ~(RX_RECEIVED);
				NVIC_EnableIRQ(USART1_IRQn);

				uint8_t chunk[MAX_MESSAGE_BYTES];
				int read_status = crc_read(PFC_USART, chunk);
				if (read_status != -1) {
					handleInput(PFC_USART, chunk);
				}
			}
			if(interruptFlags & RADIO_RECEIVED){
				NVIC_DisableIRQ(EXTI2_IRQn);
				interruptFlags &= ~RADIO_RECEIVED;
				NVIC_EnableIRQ(EXTI2_IRQn);

				//get packet
				packet_t packet;
				int size = 0;
				int failcount = 0;
				do{
					size = radio_receive(&packet, UHF_SPI);
					if(size <= 0)
						failcount++;
				}while(failcount < 5 && !packet.isPacketEnd);

				uploadData(PFC_USART, packet.pkt, packet.length);

			}
		}
		
		sleep_init();
	}

#endif

}

bool test_radio_reads_simple() {
	gpio_high(GPIOA, 8); // Enable power to UHF Transceiver
	uint32_t fails = 0;

	uint8_t retval = ax5043_read8(AX5043_SILICONREVISION, UHF_SPI);
	if (retval == 0b01010001) fails |= (1 << 0);

	retval = ax5043_read8(AX5043_SCRATCH, UHF_SPI);
	if (retval == 0b11000101) fails |= (1 << 1);

	ax5043_write8(AX5043_SCRATCH, 0xAA, UHF_SPI);

	retval = ax5043_read8(AX5043_SCRATCH, UHF_SPI);
	if (retval == 0xAA) fails |= (1 << 2);


	retval = ax5043_read8(AX5043_LPOSCREF0, UHF_SPI);
	if (retval == 0b10101000) fails |= (1 << 3);

	uint32_t wait = 33;

	return true;
}
