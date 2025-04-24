#include "AX5043.h"


void radio_init() {
    spi_config(UHF_SPI);
    uhf_init();
}

void programParametersFromRadioLab() {

}

void uhf_init() {
    gpio_high(GPIOB, 9); // Enable power to UHF Transceiver
    
    spi_startCommunication(UHF_SPI_CS);

    while(!gpio_read(GPIOB, 14)); //Wait for MISO to go HIGH 

    uint8_t initialValueOfPWRMODE = ax5043_read8(AX5043_PWRMODE);

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_RST | initialValueOfPWRMODE); //Turn on RST bit
    nop(50);
    ax5043_write8(AX5043_PWRMODE, !AX5043_PWRMODE_RST | initialValueOfPWRMODE); //Turn off RST bit

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN);

    uhf_programParametersFromRadioLab(); //TODO: Get those parameters

    int failCount = 0;
    while(!radio_autorange(AX5043_CARRIER_HZ, AX5043_XTAL_HZ)) {
        if (failCount > 3) {
            break;
        }
        failCount++;
    }

}

bool radio_autorange(int carrierHz, int xtalHz) {
	int freqa = ((uint_fast64_t)(carrierHz)<<24)/xtalHz | 1;
	ax5043_write8(AX5043_FREQA0, (freqa >> 0) & 0xFF);
	ax5043_write8(AX5043_FREQA1, (freqa >> 8) & 0xFF);
	ax5043_write8(AX5043_FREQA2, (freqa >> 16) & 0xFF);
	ax5043_write8(AX5043_FREQA3, (freqa >> 24) & 0xFF);
	
    ax5043_write8(AX5043_PLLRANGINGA, AX5043_PLLRANGINGA_VCORA);

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY | 0b11 << 5); //Not sure if i need to do the shifting but the normal reset value has REFEN and XOEN on
    while(!ax5043_read8(AX5043_XTALSTATUS)); //Wait for crystal to be ready 
    
	ax5043_write8(AX5043_PLLRANGINGA, ax5043_read8(AX5043_PLLRANGINGA) | AX5043_PLLRANGINGA_RNGSTART); // start ranging 
	
    while(!(ax5043_read8(AX5043_PLLRANGINGA) & (AX5043_PLLRANGINGA_RNGSTART))); //Wait for RNGSTART to read 0 indicating it is done

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN | 0b11 << 5);

    if (ax5043_read8(AX5043_PLLRANGINGA) & AX5043_PLLRANGINGA_RNGERR) {
        return false; //Indicates an error in auto ranging, try again
    }

    return true;
}



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

    spi_transmitReceive(UHF_SPI, addr, discard, 2, false);
    spi_transmitReceive(UHF_SPI, NULL, regVal, 1, false);

    spi_stopCommunication(UHF_SPI_CS);

    return regVal[0];
}

void ax5043_write8(uint8_t address, uint8_t data) {
    uint8_t spiDATA[2];
	spiDATA[0] = (uint8_t)address | 0x80;
	spiDATA[1] = data;


    spi_startCommunication(UHF_SPI_CS);
    spi_transmitReceive(UHF_SPI, &spiDATA, NULL, 2, false);

    spi_stopCommunication(UHF_SPI_CS);

    int test = 33;
}

