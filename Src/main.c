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

//	printMsg("START!\r\n");

	radio_init();
	packet_t packet;
	for(int i = 0; i<256; i++){
		packet.pkt[i] = 0;
	}
	// while(1){
	// 	tx_black_magic(SPI1);
	// 	delay_ms(1000);
	// }
	ax5043_set_registers_rx(UHF_SPI);
	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, UHF_SPI);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLRX, UHF_SPI);
	gpio_high(GPIOC, 9);
	delay_ms(1000);
	printMsg("INITIAL RSSI: %d", ax5043_read8(AX5043_RSSI, UHF_SPI));
	printMsg("INITIAL AGCCOUNTER: %d", ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI));
	// ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY, UHF_SPI);
	// delay_ms(1000);
	// tx_carrier_wave(SPI2);
	int rssi = ax5043_read8(AX5043_RSSI, UHF_SPI);
	int agc = ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI);
	while(1){
		// rssi = ax5043_read8(AX5043_RSSI, UHF_SPI);
		// agc = ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI);
		 int fifocount = ax5043_read8(AX5043_FIFOCOUNT0, UHF_SPI) | ax5043_read8(AX5043_FIFOCOUNT1, UHF_SPI) << 8;
		// if(fifocount > 0){
		 	printMsg("FILLED!!!");
		// 	int size = radio_receive(&packet, UHF_SPI);
		// 	for(int i = 0; i<size; i++){
		// 		printMsg("%d\t", packet.pkt[i]);
		// 	}
		// 	printMsg("\r\n");
		// 	for(int i = 0; i<256; i++){
		// 			packet.pkt[i] = 0;
		// 		}
		// 	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, UHF_SPI);
		// }
	}
	
//	 uint8_t arr[200];
//	 for(uint8_t i = 0; i<200; i++){
//	 	arr[i]  =i;
//
//	 }
	

// 	int pinstate = 0;
// 	 while(1){
// 		// tx_simple(SPI1);
// 		pinstate = ax5043_read8(AX5043_PINSTATE, SPI1);
// 		radio_transmit(200, arr, SPI1);
// //		nop(10);

// 	 }
	
	// packet_t* recieved;
	// for(int i = 0; i<256; i++){
	// 	recieved->pkt[i] = 0;
	// }
	// while(1){
	// 	//radio_receive(recieved);
	// }
    // while(true) {
    // 	blinky();
    // 	nop(1000);
    // 	bool success = test_radio_reads_simple();
    // }

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
