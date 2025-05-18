#include "AX5043.h"


void radio_init() {
    spi_config(UHF_SPI);
    uhf_init();
}

void uhf_programParametersFromRadioLab() {
	ax5043_write8(AX5043_MODULATION     ,                              			0x08);
	ax5043_write8(AX5043_ENCODING       ,                              			0x00);
	ax5043_write8(AX5043_FRAMING        ,                              			0x24);
	ax5043_write8(AX5043_PINFUNCSYSCLK  ,                              			0x01);
	ax5043_write8(AX5043_PINFUNCDCLK    ,                              			0x01);
	ax5043_write8(AX5043_PINFUNCDATA    ,                              			0x01);
	ax5043_write8(AX5043_PINFUNCANTSEL  ,                              			0x01);
	ax5043_write8(AX5043_PINFUNCPWRAMP  ,                              			0x07);
	ax5043_write8(AX5043_WAKEUPXOEARLY  ,                              			0x01);
	ax5043_write8(AX5043_IFFREQ1        ,                              			0x15);
	ax5043_write8(AX5043_IFFREQ0        ,                              			0xFA);
	ax5043_write8(AX5043_DECIMATION     ,                              			0x01);
	ax5043_write8(AX5043_RXDATARATE2    ,                              			0x00);
	ax5043_write8(AX5043_RXDATARATE1    ,                              			0x34);
	ax5043_write8(AX5043_RXDATARATE0    ,                              			0x00);
	ax5043_write8(AX5043_MAXDROFFSET2   ,                              			0x00);
	ax5043_write8(AX5043_MAXDROFFSET1   ,                              			0x00);
	ax5043_write8(AX5043_MAXDROFFSET0   ,                              			0x00);
	ax5043_write8(AX5043_MAXRFOFFSET2   ,                              			0x80);
	ax5043_write8(AX5043_MAXRFOFFSET1   ,                              			0x03);
	ax5043_write8(AX5043_MAXRFOFFSET0   ,                              			0x4D);
	ax5043_write8(AX5043_FSKDMAX1       ,                              			0x00);
	ax5043_write8(AX5043_FSKDMAX0       ,                              			0xA6);
	ax5043_write8(AX5043_FSKDMIN1       ,                              			0xFF);
	ax5043_write8(AX5043_FSKDMIN0       ,                              			0x5A);
	ax5043_write8(AX5043_AMPLFILTER     ,                              			0x00);
	ax5043_write8(AX5043_RXPARAMSETS    ,                              			0xF4);
	ax5043_write8(AX5043_AGCGAIN0       ,                              			0x73);
	ax5043_write8(AX5043_AGCTARGET0     ,                              			0x84);
	ax5043_write8(AX5043_TIMEGAIN0      ,                              			0xD8);
	ax5043_write8(AX5043_DRGAIN0        ,                              			0xD2);
	ax5043_write8(AX5043_PHASEGAIN0     ,                              			0xC3);
	ax5043_write8(AX5043_FREQUENCYGAINA0,                              			0x0F);
	ax5043_write8(AX5043_FREQUENCYGAINB0,                              			0x1F);
	ax5043_write8(AX5043_FREQUENCYGAINC0,                              			0x04);
	ax5043_write8(AX5043_FREQUENCYGAIND0,                              			0x04);
	ax5043_write8(AX5043_AMPLITUDEGAIN0 ,                              			0x06);
	ax5043_write8(AX5043_FREQDEV10      ,                              			0x00);
	ax5043_write8(AX5043_FREQDEV00      ,                              			0x00);
	ax5043_write8(AX5043_BBOFFSRES0     ,                              			0x00);
	ax5043_write8(AX5043_AGCGAIN1       ,                              			0x73);
	ax5043_write8(AX5043_AGCTARGET1     ,                              			0x84);
	ax5043_write8(AX5043_AGCAHYST1      ,                              			0x00);
	ax5043_write8(AX5043_AGCMINMAX1     ,                              			0x00);
	ax5043_write8(AX5043_TIMEGAIN1      ,                              			0xD6);
	ax5043_write8(AX5043_DRGAIN1        ,                              			0xD1);
	ax5043_write8(AX5043_PHASEGAIN1     ,                              			0xC3);
	ax5043_write8(AX5043_FREQUENCYGAINA1,                              			0x0F);
	ax5043_write8(AX5043_FREQUENCYGAINB1,                              			0x1F);
	ax5043_write8(AX5043_FREQUENCYGAINC1,                              			0x04);
	ax5043_write8(AX5043_FREQUENCYGAIND1,                              			0x04);
	ax5043_write8(AX5043_AMPLITUDEGAIN1 ,                              			0x06);
	ax5043_write8(AX5043_FREQDEV11      ,                              			0x00);
	ax5043_write8(AX5043_FREQDEV01      ,                              			0x32);
	ax5043_write8(AX5043_FOURFSK1       ,                              			0x16);
	ax5043_write8(AX5043_BBOFFSRES1     ,                              			0x00);
	ax5043_write8(AX5043_AGCGAIN3       ,                              			0xFF);
	ax5043_write8(AX5043_AGCTARGET3     ,                              			0x84);
	ax5043_write8(AX5043_AGCAHYST3      ,                              			0x00);
	ax5043_write8(AX5043_AGCMINMAX3     ,                              			0x00);
	ax5043_write8(AX5043_TIMEGAIN3      ,                              			0xD5);
	ax5043_write8(AX5043_DRGAIN3        ,                              			0xD0);
	ax5043_write8(AX5043_PHASEGAIN3     ,                              			0xC3);
	ax5043_write8(AX5043_FREQUENCYGAINA3,                              			0x0F);
	ax5043_write8(AX5043_FREQUENCYGAINB3,                              			0x1F);
	ax5043_write8(AX5043_FREQUENCYGAINC3,                              			0x08);
	ax5043_write8(AX5043_FREQUENCYGAIND3,                              			0x08);
	ax5043_write8(AX5043_AMPLITUDEGAIN3 ,                              			0x06);
	ax5043_write8(AX5043_FREQDEV13      ,                              			0x00);
	ax5043_write8(AX5043_FREQDEV03      ,                              			0x32);
	ax5043_write8(AX5043_FOURFSK3       ,                              			0x16);
	ax5043_write8(AX5043_BBOFFSRES3     ,                              			0x00);
	ax5043_write8(AX5043_MODCFGF        ,                              			0x03);
	ax5043_write8(AX5043_FSKDEV2        ,                              			0x00);
	ax5043_write8(AX5043_FSKDEV1        ,                              			0x4E);
	ax5043_write8(AX5043_FSKDEV0        ,                              			0xC5);

	ax5043_write8(AX5043_MODCFGA        ,                              			0x05);
	ax5043_write8(AX5043_TXRATE2        ,                              			0x01);
	ax5043_write8(AX5043_TXRATE1        ,                              			0x3B);
	ax5043_write8(AX5043_TXRATE0        ,                              			0x14);
	ax5043_write8(AX5043_TXPWRCOEFFB1   ,                              			0x0F);
	ax5043_write8(AX5043_TXPWRCOEFFB0   ,                              			0xFF);
	ax5043_write8(AX5043_PLLVCOI        ,                              			0x98);
	ax5043_write8(AX5043_PLLRNGCLK      ,                              			0x04);
	ax5043_write8(AX5043_BBTUNE         ,                              			0x01);
	ax5043_write8(AX5043_BBOFFSCAP      ,                              			0x77);
	ax5043_write8(AX5043_PKTADDRCFG     ,                              			0x01);
	ax5043_write8(AX5043_PKTLENCFG      ,                              			0x80);
	ax5043_write8(AX5043_PKTLENOFFSET   ,                              			0x00);
	ax5043_write8(AX5043_PKTMAXLEN      ,                              			0xC8);
	ax5043_write8(AX5043_MATCH0PAT3     ,                              			0xAA);
	ax5043_write8(AX5043_MATCH0PAT2     ,                              			0xCC);
	ax5043_write8(AX5043_MATCH0PAT1     ,                              			0xAA);
	ax5043_write8(AX5043_MATCH0PAT0     ,                              			0xCC);
	ax5043_write8(AX5043_MATCH1PAT1     ,                              			0x55);
	ax5043_write8(AX5043_MATCH1PAT0     ,                              			0x55);
	ax5043_write8(AX5043_MATCH1LEN      ,                              			0x8A);
	ax5043_write8(AX5043_MATCH1MAX      ,                              			0x0A);
	ax5043_write8(AX5043_TMGTXBOOST     ,                              			0x3E);
	ax5043_write8(AX5043_TMGTXSETTLE    ,                              			0x31);
	ax5043_write8(AX5043_TMGRXBOOST     ,                              			0x3E);
	ax5043_write8(AX5043_TMGRXSETTLE    ,                              			0x31);

	ax5043_write8(AX5043_TMGRXOFFSACQ   ,                              			0x00);
	ax5043_write8(AX5043_TMGRXCOARSEAGC ,                              			0x7F);
	ax5043_write8(AX5043_TMGRXRSSI      ,                              			0x03);
	ax5043_write8(AX5043_TMGRXPREAMBLE2 ,                              			0x17);
	ax5043_write8(AX5043_RSSIABSTHR     ,                              			0xEB);
	ax5043_write8(AX5043_BGNDRSSITHR    ,                              			0x00);
	ax5043_write8(AX5043_PKTCHUNKSIZE   ,                              			0x0D);
	ax5043_write8(AX5043_PKTACCEPTFLAGS ,                              			0x20);
	//ax5043_write8(AX5043_DACVALUE1      ,                              			0x00);// Also sucks ass
	// ax5043_write8(AX5043_DACVALUE0      ,                              			0x00); //Sucks ass, will break everything
	ax5043_write8(AX5043_DACCONFIG      ,                              			0x00);
	ax5043_write8(AX5043_REF            ,                              			0x03);
	
	ax5043_write8(AX5043_XTALOSC        ,                              			0x04);
	ax5043_write8(AX5043_XTALAMPL       ,                              			0x00);
	ax5043_write8(AX5043_0xF1C          ,                              			0x07);
	ax5043_write8(AX5043_0xF21          ,                              			0x68);
	ax5043_write8(AX5043_0xF22          ,                              			0xFF);
	ax5043_write8(AX5043_0xF23          ,                              			0x84);
	ax5043_write8(AX5043_0xF26          ,                              			0x98);
	ax5043_write8(AX5043_0xF34          ,                              			0x28);
	ax5043_write8(AX5043_0xF35          ,                              			0x11);
	ax5043_write8(AX5043_0xF44          ,                              			0x25);
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x04);
	
}

void uhf_init() {

    gpio_low(GPIOB, 9); // Disable power to UHF Transceiver 
    nop(10000000);
    gpio_high(GPIOB, 9); // Enable power to UHF Transceiver
    //power cycle the chip to clear previous auto ranges
    nop(10000000);

    spi_startCommunication(UHF_SPI_CS);

    while(!gpio_read(GPIOA, 6)); //Wait for MISO to go HIGH 

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_RST); //Turn on RST bit
  	nop(1000);
    ax5043_write8(AX5043_PWRMODE,  AX5043_PWRMODE_POWERDOWN | AX5043_PWRMODE_DEFAULTVALUES); //Turn off RST bit

    uhf_programParametersFromRadioLab(); //TODO: Get those parameters
	
	
    int failCount = 0;
    while(!radio_autorange(AX5043_CARRIER_HZ, AX5043_XTAL_HZ)) {
        if (failCount > 3) {
            break;
        }
        failCount++;
    }

}

bool radio_autorange(float carrierHz, int xtalHz) {
	
    uint8_t printRegister = 0;

	 uint64_t freqa = (uint64_t)(carrierHz / xtalHz * (1<<24) +.5) |1;

	ax5043_write8(AX5043_FREQA0, (freqa >> 0) & 0xFF);
	ax5043_write8(AX5043_FREQA1, (freqa >> 8) & 0xFF);
	ax5043_write8(AX5043_FREQA2, (freqa >> 16) & 0xFF);
	ax5043_write8(AX5043_FREQA3, (freqa >> 24) & 0xFF);
	
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY | AX5043_PWRMODE_DEFAULTVALUES); // Set to STANDBY
	gpio_high(GPIOC, 9); //Enable clock for crystal

	while(!ax5043_read8(AX5043_XTALSTATUS)); //Wait for crystal to be ready
    
	ax5043_write8(AX5043_PLLRANGINGA, AX5043_PLLRANGINGA_VCORA | AX5043_PLLRANGINGA_RNGSTART); // start ranging 

	while (!(ax5043_read8(AX5043_IRQREQUEST1) & 0x10)); // Check for Error

    while((ax5043_read8(AX5043_PLLRANGINGA) & (AX5043_PLLRANGINGA_RNGSTART))); //Wait for RNGSTART to read 0 indicating it is done

    printRegister = ax5043_read8(AX5043_PLLRANGINGA);

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN | AX5043_PWRMODE_DEFAULTVALUES);

	gpio_low(GPIOC, 9); //Enable clock for crystal

    if (ax5043_read8(AX5043_PLLRANGINGA) & AX5043_PLLRANGINGA_RNGERR) {
    	return false; //Indicates an error in auto ranging, try again
    }

    return true;
}


void radio_transmit(int numBytes, uint8_t* bytesToSend) {
    
    int bytesSent = 0;
    int pktCurrentIndex = 0;
    int packetSize = 0; 
    int spaceLeftInFIFO = 0;
    
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX | AX5043_PWRMODE_DEFAULTVALUES);
    while(!(ax5043_read8(AX5043_POWSTAT) & AX5043_POWSTAT_SVMODEM)); //Waiting for Modem to be ready

    while (bytesSent < numBytes) {
        
        spaceLeftInFIFO = (ax5043_read8(AX5043_FIFOFREE1) << 8) | ax5043_read8(AX5043_FIFOFREE0); 

        if (spaceLeftInFIFO > numBytes + 3 - bytesSent) { //Adding three bytes for Header Byte, Length Byte, and Flag Byte
            packetSize = numBytes + 3 - bytesSent;
        } else {
            packetSize = spaceLeftInFIFO;
        }


        ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_DATA_COMMAND); //Header byte indicating DATA command
        ax5043_write8(AX5043_FIFODATA, packetSize - 2); //Subtracting two to account for header and length byte 

        uint8_t flags = 0;

        if (pktCurrentIndex == 0) {
            flags |= AX5043_TX_FLAGS_PKTSTART;
        }

        //If the amount of bytes about to be sent is equal or more than numBytes than must have end of packet
        if (pktCurrentIndex + packetSize - 3 >= numBytes) { 
            flags |= AX5043_TX_FLAGS_PKTEND;
        }

        ax5043_write8(AX5043_FIFODATA, flags);


        for (; pktCurrentIndex < packetSize - 3; pktCurrentIndex++) {
            ax5043_write8(AX5043_FIFODATA, bytesToSend[pktCurrentIndex]);
        }

        ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT);

        //Wait for transmitting to be active by making sure it changes from IDLE and that FIFO is being filled
        while(!ax5043_read8(AX5043_RADIOSTATE) && ((ax5043_read8(AX5043_FIFOFREE1) << 8) | ax5043_read8(AX5043_FIFOFREE0) < 10));

        bytesSent += packetSize - 3;

        while(ax5043_read8(AX5043_RADIOSTATE)); //Wait for RadioState to show IDLE

    } 

}
 
 
bool radio_receive(packet_t* received_packet) {
	
	if (ax5043_read8(AX5043_FIFOCOUNT0) > 0) {
		uint8_t header = ax5043_read8(AX5043_FIFODATA);
		uint8_t length = ax5043_read8(AX5043_FIFODATA);
		uint8_t flags = ax5043_read8(AX5043_FIFODATA);
		received_packet->isPacketStart = flags & AX5043_TX_FLAGS_PKTSTART;
		received_packet->isPacketEnd = flags & AX5043_TX_FLAGS_PKTEND;
		received_packet->length = length - 1;
		
		for (int i = 0; i < length - 1; i++) {
			if (header == AX5043_FIFODATA_DATA_COMMAND) { //Only read it if its a data command 
				(received_packet->pkt)[i] = ax5043_read8(AX5043_FIFODATA);
			}
		}
		
		return true;
	}

	return false; 
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

