// UHF (SPI1) will be on 433 MHz downlink
// VHF will be on 150 MHz uplink

#include "AX5043.h"


void radio_init() {
    spi_config(UHF_SPI);
    uhf_init();
    vhf_init();
}



void uhf_init() {
    gpio_high(GPIOB, 9); // Enable power to UHF Transceiver
    return;

    //Setting the reset modes
    radio_spiWriteReg(AX5043_PWRMODE, AX5043_PWRMODE_RST); // Turn on reset bit
    radio_spiWriteReg(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN); // Set it to power down (only register file stays on) while also clearing reset bit

    // Setting parameters
    
    // Auto ranging
    radio_spiWriteReg(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY);
    radio_autorange(AX5043_CARRIER_HZ, AX5043_XTAL_HZ);
    radio_spiWriteReg(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN);

}

int radio_autorange(int carrierHz, int xtalHz) {
	int freqa = ((uint_fast64_t)(carrierHz)<<24)/xtalHz | 1;
	radio_spiWriteReg(AX5043_FREQA0, (freqa >> 0) & 0xFF);
	radio_spiWriteReg(AX5043_FREQA1, (freqa >> 8) & 0xFF);
	radio_spiWriteReg(AX5043_FREQA2, (freqa >> 16) & 0xFF);
	radio_spiWriteReg(AX5043_FREQA3, (freqa >> 24) & 0xFF);
	
	radio_spiWriteReg(AX5043_PLLRANGINGA, 0x18); // start ranging 
	
	int count = 0;
	while (!(radio_spiReadReg(AX5043_IRQREQUEST1) & 0x10)) {
		count++;
		if (count > 0xFFFF) {
			break;
		}
	}

	if (radio_spiReadReg(AX5043_PLLRANGINGA) & (0x20|0x10)) { // check for "ranging error" and "ranging active"
		return 1;
	} else {
		// dmsg("Synthesizer autorange OK");
		return 0;
	}
}

void radio_write8(int addr, int data) {
	radio_write_far(addr, data);
}


void vhf_init() {
    gpio_high(GPIOA, 8); //Enable power to VHF Transceiver
}

#if 0
int radio_write_far(int addr, int data) {
//	no(0xFF);
	GPIO_PRT3->DR_CLR = 0x01; // activate chip select
    GPIO_PRT3->DR_CLR = 0x01; // activate chip select
	while(!(GPIO_PRT2->PS & 0x02)); // wait for radio to assert miso 
	SCB1->TX_FIFO_WR = ((addr >> 8) | 0xF0); // send address, first bit write
//	dreg("a", ((addr >> 8) | 0xF0));
	SCB1->TX_FIFO_WR = addr & 0xFF;
//	dreg("a", (addr & 0xFF));
	SCB1->TX_FIFO_WR = data & 0xFF; // send data
	while((SCB1->RX_FIFO_STATUS & 0xF) < 3); // wait until data received 
	GPIO_PRT3->DR_SET = (1 << 0); // deactivate chip select
	while(GPIO_PRT2->PS & 0x02); // wait for radio to let go of miso 
	return (SCB1->RX_FIFO_RD<<16) | (SCB1->RX_FIFO_RD<<8) | SCB1->RX_FIFO_RD; 
}
#endif

uint8_t radio_spiReadReg(uint16_t address) {
    uint8_t addr[2];
    addr[0] = address >> 8;
    addr[0] |=  0xF0;   // Set left 4 bits to 0b1111
    addr[0] &= ~0x80;   // Clear left most bit

    addr[1] = address &= 0x00FF;    // 8 rightmost bits go to addr[1]
    
    uint8_t regVal = 0xFF;

    spi_startCommunication(UHF_SPI_CS);

    spi_transmitReceive(UHF_SPI, addr, NULL, 2, false);
    spi_transmitReceive(UHF_SPI, NULL, &regVal, 1, false);

    spi_stopCommunication(UHF_SPI_CS);

    return regVal;
}

void radio_spiWriteReg(void *address, uint8_t data) {
//    spiDATA[0] = (uint8_t) address & 0x7F; //Set MSB to 0
//    spiDATA[1] = data;
//    spiDATA[0] = 0b01110000;
//    spiDATA[1] = 0b00000001;
//    spiDATA[2] = 0b01010101;	// Dummy data

    uint8_t spiDATA = 0b10000000;

    uint8_t spiOut0 = (uint8_t) 0xFF;
    uint8_t spiOut1 = (uint8_t) 0xFF;

    spi_startCommunication(UHF_SPI_CS);
    nop(100);
    spi_transmitReceive(UHF_SPI, &spiDATA, &spiOut0, 1, false);
    spi_transmitReceive(UHF_SPI, NULL, &spiOut1, 1, false);

    spi_stopCommunication(UHF_SPI_CS);

    int test = 33;
}

