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
	uint64_t lastUplinkTime = getSysTime();
	while (1) {
		while(interruptFlags){
			if(interruptFlags & RX_RECEIVED){
				__disable_irq();
				interruptFlags &= ~(RX_RECEIVED);
				__enable_irq();

				uint8_t chunk[MAX_MESSAGE_BYTES];
				int read_status = crc_read(PFC_USART, chunk);
				if (read_status != -1) {
					handleInput(PFC_USART, chunk);
				}
			}
			else if(interruptFlags & RADIO_RECEIVED){
				__disable_irq();
				interruptFlags &= ~RADIO_RECEIVED;
				__enable_irq();

				//get packet
				packet_t packet;
				int size = 0;
				int failcount = 0;
				do{
					size = radio_receive(&packet, UHF_SPI);
					if(size <= 0)
						failcount++;
				}while(failcount < 5 && !packet.isPacketEnd);

				interruptFlags |= RADIO_RX_ON;
				lastUplinkTime = getSysTime();

				uploadData(PFC_USART, packet.pkt, packet.length);

			}else if(interruptFlags & RADIO_RX_ON){
				if (getSysTime() > lastUplinkTime + FIVEMINUTES){ //timeout, go back to sleep
					interruptFlags &= ~RADIO_RX_ON;
					ax5043_receiverWOR();
				}
				ax5043_receiverOn();
			} else if(interruptFlags & RADIO_COMMS_FINISHED){
				__disable_irq();
				interruptFlags &= ~(RADIO_RX_ON | RADIO_COMMS_FINISHED);
				__enable_irq();
				ax5043_receiverWOR();
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
