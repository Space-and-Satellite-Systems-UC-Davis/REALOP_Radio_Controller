#include <stdint.h>
#include "platform_init.h"
#include "Radio/AX5043.h"
#include <TestDefinition.h>
#include <globals.h>
#include "Sleep/sleep.h"
#include <Flight_Computer/Intercomm.h>

#define RUN_TEST	1	// 0 = run, 1 = run a very specific test
#define TEST_ID 	1	// ID of the test to run in case RUN_TEST = 1

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
		ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, UHF_SPI);
	// ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLRX, UHF_SPI);
	ax5043_receiverWOR();
	gpio_high(GPIOC, 9);
	delay_ms(1000);
	printMsg("INITIAL RSSI: %d", ax5043_read8(AX5043_RSSI, UHF_SPI));
	printMsg("INITIAL AGCCOUNTER: %d", ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI));
	delay_ms(1000);
	uint64_t lastUplinkTime = getSysTime();
	char buffer[1000];
	while (1) {
		printMsg("LOOP %x\r\n", interruptFlags);
		while(interruptFlags){
			if(interruptFlags & RX_RECEIVED){
				__disable_irq();
				interruptFlags &= ~(RX_RECEIVED);
				__enable_irq();
				printMsg("Rx-received\r\n");
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
				printMsg("Radio received\r\n");
				//get packet
				packet_t packet;
				int size = 0;
				int failcount = 0;
				int index = 0;
				do{
					size = radio_receive(&packet, UHF_SPI);
					if(size <= 0)
						failcount++;
					else{
						memcpy(buffer + index, packet.pkt, packet.length);
						index += size;
					}
				}while(failcount < 5 && !packet.isPacketEnd);

				interruptFlags |= RADIO_RX_ON;
				ax5043_receiverOn();
				lastUplinkTime = getSysTime();
				printMsg("TX DATA\r\n");
				uploadData(PFC_USART, buffer, index);
				printMsg("DONE TX");
			}else if(interruptFlags & RADIO_RX_ON){
				if (getSysTime() > lastUplinkTime + 2000){//FIVEMINUTES){ //timeout, go back to sleep
					interruptFlags &= ~RADIO_RX_ON;
					ax5043_receiverWOR();
				}
				printMsg("At %d", getSysTime() - lastUplinkTime);
				
			} else if(interruptFlags & RADIO_COMMS_FINISHED){
				__disable_irq();
				interruptFlags &= ~(RADIO_RX_ON | RADIO_COMMS_FINISHED);
				__enable_irq();
				ax5043_receiverWOR();
				printMsg("radio done\r\n");
			}
		}
		
		// sleep_init();
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
