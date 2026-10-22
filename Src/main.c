#include <stdint.h>
#include "platform_init.h"
#include "Radio/AX5043.h"
#include <TestDefinition.h>
#include <globals.h>
#include "Sleep/sleep.h"
#include <Flight_Computer/Intercomm.h>
#include <stdatomic.h>

#define RUN_TEST	0	// 0 = run, 1 = run a very specific test
#define TEST_ID 	0	// ID of the test to run in case RUN_TEST = 1

volatile atomic_int interruptFlags = 0;

#define BUFFSIZE  2000
char buffer[BUFFSIZE];
int BUFFINDEX;

#define RECEIVER_INTERVAL 1000 + 300 //1000 per receive plus ample buffer

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
	for(int i = 0; i<BUFFSIZE; i++){
		buffer[i] = 0;
	}
	ax5043_set_registers_rx(UHF_SPI);
	ax5043_set_registers_rxwor(UHF_SPI);
	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, UHF_SPI);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_WORRX, UHF_SPI);
	gpio_high(GPIOC, 9);
	wor_config(200, UHF_SPI);
	BUFFINDEX = 0;
	uint64_t lastUplinkTime = getSysTime();
	while (1) {
		while(interruptFlags){
			if(interruptFlags & RX_RECEIVED){
				atomic_fetch_and(&interruptFlags, ~RX_RECEIVED);
				printMsg("Rx-received\r\n");
				uint8_t chunk[MAX_MESSAGE_BYTES];
				int read_status = crc_read(PFC_USART, chunk);
				if (read_status != -1) {
					handleInput(PFC_USART, chunk);
				}
			}
			else if(interruptFlags & RADIO_RECEIVED){

				atomic_fetch_and(&interruptFlags, ~RADIO_RECEIVED);

				//get packet
				packet_t packet;
				int size = 0;
				int failcount = 0;
				do{
					size = radio_receive_satellite(&packet, UHF_SPI);
					if(size <= 0)
						failcount++;
					else{
						memcpy(buffer + BUFFINDEX, packet.pkt, size);
						BUFFINDEX += size;
						// for(int i = 0; i<size; i++){
						// 	printMsg("%c", packet.pkt[i]);
						// }
					}
					if(failcount > 5){
						break;
					}
				}while(!packet.isPacketEnd);
				if(failcount > 5)
					continue;
			
				atomic_fetch_or(&interruptFlags, WOR_RECEIVED);
				lastUplinkTime = getSysTime();

			}else if(interruptFlags & WOR_RECEIVED){
				if (getSysTime() > lastUplinkTime + RECEIVER_INTERVAL){
					uploadData(PFC_USART, buffer, BUFFINDEX);
					BUFFINDEX = 0;
					atomic_fetch_and(&interruptFlags, ~WOR_RECEIVED);
				}
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
