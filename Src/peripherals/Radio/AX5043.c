// UHF (SPI1) will be on 433 MHz downlink
// VHF will be on 150 MHz uplink

#include "AX5043.h"


void radio_process(){
	// radio_reset
	radio_write(0x02, 0x80); // reset
	radio_write(0x02, 0x60);

	// from radiolab, needs radio_write8
	ax5043_set_registers()

	// autorange to needed freq and stuff???
	radio_autorange()

	radio_rx_init()
		radio_mode_rx()
			radio_write(AX5043_PWRMODE, 0x69); // power mode to receiver
			while (!(radio_read(AX5043_POWSTAT) & 0x8)); // wait for SVMODEM bit
		ax5043_set_registers_rx(); // Radiolab
	ax5043_set_registers_rx_cont()

	// TX
	radio_tx_init()
		radio_mode_tx()
			radio_write(AX5043_PWRMODE, 0x6D); // power mode to full transmit
			while (!(radio_read(AX5043_POWSTAT) & 0x8)); // wait for SVMODEM bit which indicate transmit mode success
		ax5043_set_registers_tx()

	radio_tx_packet
}

void radio_init() {
    spi_config(UHF_SPI);
    uhf_init();
}




void uhf_init() {
    gpio_high(GPIOB, 9); // Enable power to UHF Transceiver
    return;

    //Setting the reset modes
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_RST); // Turn on reset bit
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN); // Set it to power down (only register file stays on) while also clearing reset bit

    // Setting parameters
    
    // Auto ranging
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY);
    radio_autorange(AX5043_CARRIER_HZ, AX5043_XTAL_HZ);
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN);

}

int radio_autorange(int carrierHz, int xtalHz) {
	int freqa = ((uint_fast64_t)(carrierHz)<<24)/xtalHz | 1;
	ax5043_write8(AX5043_FREQA0, (freqa >> 0) & 0xFF);
	ax5043_write8(AX5043_FREQA1, (freqa >> 8) & 0xFF);
	ax5043_write8(AX5043_FREQA2, (freqa >> 16) & 0xFF);
	ax5043_write8(AX5043_FREQA3, (freqa >> 24) & 0xFF);
	
	ax5043_write8(AX5043_PLLRANGINGA, 0x18); // start ranging 
	
	int count = 0;
	while (!(ax5043_read8(AX5043_IRQREQUEST1) & 0x10)) {
		count++;
		if (count > 0xFFFF) {
			break;
		}
	}

	if (ax5043_read8(AX5043_PLLRANGINGA) & (0x20|0x10)) { // check for "ranging error" and "ranging active"
		return 1;
	} else {
		// dmsg("Synthesizer autorange OK");
		return 0;
	}
}

typedef struct pin_struct
{
	GPIO_TypeDef* port;
	int num;
} pin_t;

typedef struct spi_struct
{
	SPI_TypeDef* spi_reg;
	pin_t pin;
} spi_t;

void radio_write8(spi_t* spi,  uint32_t addr, uint8_t data) {
	//    spiDATA[0] = (uint8_t) address & 0x7F; //Set MSB to 0
	//    spiDATA[1] = data;
	//    spiDATA[0] = 0b01110000;
	//    spiDATA[1] = 0b00000001;
	//    spiDATA[2] = 0b01010101;	// Dummy data

	uint8_t spiDATA = 0b10000000;

	uint8_t spiOut0 = (uint8_t) 0xFF;
	uint8_t spiOut1 = (uint8_t) 0xFF;

	spi_startCommunication(spi->pin.port, spi->pin.num);
	nop(100);
	spi_transmitReceive(UHF_SPI, &spiDATA, &spiOut0, 1, false);
	spi_transmitReceive(UHF_SPI, NULL, &spiOut1, 1, false);

	spi_stopCommunication(UHF_SPI_CS);
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

uint8_t ax5043_read8(uint32_t address) {
    uint8_t addr[2];
    addr[0] = address >> 8;
    addr[0] |=  0xF0;   // Set left 4 bits to 0b1111
    addr[0] &= (uint8_t) ~0x80;   // Clear left most bit

    addr[1] = address &= 0x00FF;    // 8 rightmost bits go to addr[1]
    
    uint8_t discard[2] = {0xFF, 0xFF};
    uint8_t regVal[1] = {0xFF};

    spi_startCommunication(UHF_SPI_CS);

    while (UHF_SPI->SR & SPI_SR_RXNE) {	// CLear RX Fifo
    	UHF_SPI->DR;
	}

    int am_here = 1;

    spi_transmitReceive(UHF_SPI, addr, discard, 2, false);
    spi_transmitReceive(UHF_SPI, NULL, regVal, 1, false);

    nop(4000);
    spi_stopCommunication(UHF_SPI_CS);

    return regVal[0];
}

void ax5043_write8(uint8_t address, uint8_t data) {
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

