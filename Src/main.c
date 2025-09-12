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

	printMsg("START!\r\n");

	radio_init();
	uint8_t arr[100];
	for(uint8_t i = 0; i<100; i++){
		arr[i] = i * 17;
	}
	packet_t packet;
	for(int i = 0; i<256; i++){
		packet.pkt[i] = 0;
	}
	 ax5043_set_registers_rx(UHF_SPI);
	// ax5043_calculate_rx_registers(UHF_SPI);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLRX, UHF_SPI);
	gpio_high(GPIOC, 9);
	delay_ms(1000);
	printMsg("INITIAL RSSI: %d", ax5043_read8(AX5043_RSSI, UHF_SPI));
	printMsg("INITIAL AGCCOUNTER: %d", ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI));
	// tx_carrier_wave(SPI2);
	while(1){
		printMsg("Transmit!\r\n");
		printMsg("RX RADIOSTATE: %d\r\n", ax5043_read8(AX5043_RADIOSTATE, UHF_SPI) );
		//   radio_transmit(100, arr, SPI2);
		tx_black_magic(SPI2);

		uint64_t start = getSysTime();
		long rssi = 0;
		long agc = 0;
		int count = 0;
		while(getSysTime() - start < 1000){
			rssi += ax5043_read8(AX5043_RSSI, UHF_SPI);
			agc += ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI);
			count++;
			// printMsg("RSSI: %d\t", ax5043_read8(AX5043_RSSI, UHF_SPI));
			// printMsg("AGC: %d\t", ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI));
		}
		printMsg("AV RSSI: %d, AV AGC: %d\r\n", rssi/count, agc/count);
		ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY, SPI2);

		if(ax5043_read8(AX5043_FIFOCOUNT0, UHF_SPI) | ax5043_read8(AX5043_FIFOCOUNT0, UHF_SPI)){
			int size = radio_receive(&packet, UHF_SPI);
			for(int i = 0; i<size; i++){
				printMsg("%d\t", packet.pkt[i]);
			}
		}

		delay_ms(1000);
		printMsg("NOT TRANSMITTING: \r\n");
		start = getSysTime();
		rssi = 0;
		agc = 0;
		count = 0;
		while(getSysTime() - start < 1000){
			rssi += ax5043_read8(AX5043_RSSI, UHF_SPI);
			agc += ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI);
			count++;
			// printMsg("RSSI: %d\t", ax5043_read8(AX5043_RSSI, UHF_SPI));
			// printMsg("AGC: %d\t", ax5043_read8(AX5043_AGCCOUNTER, UHF_SPI));
			// printMsg("PHASE: %d\r\n", ax5043_read8(AX5043_TRKPHASE1, UHF_SPI) | ax5043_read8(AX5043_TRKPHASE0, UHF_SPI));
		}
		printMsg("AV RSSI: %d, AV AGC: %d\r\n", rssi/count, agc/count);
		ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX, SPI2);
		delay_ms(1000);
		//   tx_black_magic(SPI2);
//		tx_simple(SPI1);
		// nop(10000000);
		//  bool recieved = radio_receive(packet, SPI2);
		//  if(recieved){
		//  	for(int i = 0; i<100; i++){
		//  		printMsg(packet->pkt[i]);
		//  	}
		//  }else{
		//  	printMsg("Noooooo :(\n");
		//  }
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
