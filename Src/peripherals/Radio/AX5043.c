#include "AX5043.h"


void radio_init() {
    spi_config(UHF_SPI);
	spi_config(VHF_SPI);
    uhf_init();
	vhf_init();
}

void uhf_programParametersFromRadioLab(SPI_TypeDef* spi) {
	
	ax5043_write8(AX5043_ENCODING       ,                              			0x00,spi);
	ax5043_write8(AX5043_FRAMING        ,                              			0x24,spi);
	ax5043_write8(AX5043_PINFUNCSYSCLK  ,                              			0x01,spi);
	ax5043_write8(AX5043_PINFUNCDCLK    ,                              			0x01,spi);
	ax5043_write8(AX5043_PINFUNCDATA    ,                              			0x01,spi);
	ax5043_write8(AX5043_PINFUNCANTSEL  ,                              			0x01,spi); //originally 0x01
	ax5043_write8(AX5043_PINFUNCPWRAMP  ,                              			0x07,spi);
	ax5043_write8(AX5043_WAKEUPXOEARLY  ,                              			0x01,spi);
	ax5043_write8(AX5043_IFFREQ1        ,                              			0x15,spi);
	ax5043_write8(AX5043_IFFREQ0        ,                              			0xFA,spi);
	ax5043_write8(AX5043_DECIMATION     ,                              			0x01,spi);
	ax5043_write8(AX5043_RXDATARATE2    ,                              			0x00,spi);
	ax5043_write8(AX5043_RXDATARATE1    ,                              			0x34,spi);
	ax5043_write8(AX5043_RXDATARATE0    ,                              			0x00,spi);
	ax5043_write8(AX5043_MAXDROFFSET2   ,                              			0x00,spi);
	ax5043_write8(AX5043_MAXDROFFSET1   ,                              			0x00,spi);
	ax5043_write8(AX5043_MAXDROFFSET0   ,                              			0x00,spi);
	ax5043_write8(AX5043_MAXRFOFFSET2   ,                              			0x80,spi);
	ax5043_write8(AX5043_MAXRFOFFSET1   ,                              			0x00,spi);
	ax5043_write8(AX5043_MAXRFOFFSET0   ,                              			0x00,spi);
	ax5043_write8(AX5043_AMPLFILTER     ,                              			0x00,spi);
	ax5043_write8(AX5043_RXPARAMSETS    ,                              			0xF4,spi);
	ax5043_write8(AX5043_AGCGAIN0       ,                              			0x73,spi);
	ax5043_write8(AX5043_AGCTARGET0     ,                              			0x84,spi);
	ax5043_write8(AX5043_TIMEGAIN0      ,                              			0xD8,spi);
	ax5043_write8(AX5043_DRGAIN0        ,                              			0xD2,spi);
	ax5043_write8(AX5043_PHASEGAIN0     ,                              			0xC3,spi);
	ax5043_write8(AX5043_FREQUENCYGAINA0,                              			0x26,spi);
	ax5043_write8(AX5043_FREQUENCYGAINB0,                              			0x0A,spi);
	ax5043_write8(AX5043_FREQUENCYGAINC0,                              			0x1F,spi);
	ax5043_write8(AX5043_FREQUENCYGAIND0,                              			0x1F,spi);
	ax5043_write8(AX5043_AMPLITUDEGAIN0 ,                              			0x06,spi);
	ax5043_write8(AX5043_FREQDEV10      ,                              			0x00,spi);
	ax5043_write8(AX5043_FREQDEV00      ,                              			0x00,spi);
	ax5043_write8(AX5043_BBOFFSRES0     ,                              			0x00,spi);
	ax5043_write8(AX5043_AGCGAIN1       ,                              			0x73,spi);
	ax5043_write8(AX5043_AGCTARGET1     ,                              			0x84,spi);
	ax5043_write8(AX5043_AGCAHYST1      ,                              			0x00,spi);
	ax5043_write8(AX5043_AGCMINMAX1     ,                              			0x00,spi);
	ax5043_write8(AX5043_TIMEGAIN1      ,                              			0xD6,spi);
	ax5043_write8(AX5043_DRGAIN1        ,                              			0xD1,spi);
	ax5043_write8(AX5043_PHASEGAIN1     ,                              			0xC3,spi);
	ax5043_write8(AX5043_FREQUENCYGAINA1,                              			0x26,spi);
	ax5043_write8(AX5043_FREQUENCYGAINB1,                              			0x0A,spi);
	ax5043_write8(AX5043_FREQUENCYGAINC1,                              			0x1F,spi);
	ax5043_write8(AX5043_FREQUENCYGAIND1,                              			0x1F,spi);
	ax5043_write8(AX5043_AMPLITUDEGAIN1 ,                              			0x06,spi);
	ax5043_write8(AX5043_FREQDEV11      ,                              			0x00,spi);
	ax5043_write8(AX5043_FREQDEV01      ,                              			0x2D,spi);
	ax5043_write8(AX5043_FOURFSK1       ,                              			0x16,spi);
	ax5043_write8(AX5043_BBOFFSRES1     ,                              			0x00,spi);
	ax5043_write8(AX5043_AGCGAIN3       ,                              			0xFF,spi);
	ax5043_write8(AX5043_AGCTARGET3     ,                              			0x84,spi);
	ax5043_write8(AX5043_AGCAHYST3      ,                              			0x00,spi);
	ax5043_write8(AX5043_AGCMINMAX3     ,                              			0x00,spi);
	ax5043_write8(AX5043_TIMEGAIN3      ,                              			0xD5,spi);
	ax5043_write8(AX5043_DRGAIN3        ,                              			0xD0,spi);
	ax5043_write8(AX5043_PHASEGAIN3     ,                              			0xC3,spi);
	ax5043_write8(AX5043_FREQUENCYGAINA3,                              			0x26,spi);
	ax5043_write8(AX5043_FREQUENCYGAINB3,                              			0x0A,spi);
	ax5043_write8(AX5043_FREQUENCYGAINC3,                              			0x1F,spi);
	ax5043_write8(AX5043_FREQUENCYGAIND3,                              			0x1F,spi);
	ax5043_write8(AX5043_AMPLITUDEGAIN3 ,                              			0x06,spi);
	ax5043_write8(AX5043_FREQDEV13      ,                              			0x00,spi);
	ax5043_write8(AX5043_FREQDEV03      ,                              			0x2D,spi);
	ax5043_write8(AX5043_FOURFSK3       ,                              			0x16,spi);
	ax5043_write8(AX5043_BBOFFSRES3     ,                              			0x00,spi);
	

	
	ax5043_write8(AX5043_PLLVCOI        ,                              			0x95,spi);
	ax5043_write8(AX5043_PLLRNGCLK      ,                              			0x04,spi);
	ax5043_write8(AX5043_BBTUNE         ,                              			0x01,spi);
	ax5043_write8(AX5043_BBOFFSCAP      ,                              			0x77,spi);
	ax5043_write8(AX5043_PKTADDRCFG     ,                              			0x01,spi);
	ax5043_write8(AX5043_PKTLENCFG      ,                              			0x80,spi);
	ax5043_write8(AX5043_PKTLENOFFSET   ,                              			0x00,spi);
	ax5043_write8(AX5043_PKTMAXLEN      ,                              			0xC8,spi);
	ax5043_write8(AX5043_MATCH0PAT3     ,                              			0xAA,spi);
	ax5043_write8(AX5043_MATCH0PAT2     ,                              			0xCC,spi);
	ax5043_write8(AX5043_MATCH0PAT1     ,                              			0xAA,spi);
	ax5043_write8(AX5043_MATCH0PAT0     ,                              			0xCC,spi);
	ax5043_write8(AX5043_MATCH1PAT1     ,                              			0x55,spi);
	ax5043_write8(AX5043_MATCH1PAT0     ,                              			0x55,spi);
	ax5043_write8(AX5043_MATCH1LEN      ,                              			0x8A,spi);
	ax5043_write8(AX5043_MATCH1MAX      ,                              			0x0A,spi);
	ax5043_write8(AX5043_TMGTXBOOST     ,                              			0x3E,spi);
	ax5043_write8(AX5043_TMGTXSETTLE    ,                              			0x31,spi);
	ax5043_write8(AX5043_TMGRXBOOST     ,                              			0x3E,spi);
	ax5043_write8(AX5043_TMGRXSETTLE    ,                              			0x31,spi);
	ax5043_write8(AX5043_TMGRXOFFSACQ   ,                              			0x00,spi);
	ax5043_write8(AX5043_TMGRXCOARSEAGC ,                              			0x7F,spi);
	ax5043_write8(AX5043_TMGRXRSSI      ,                              			0x03,spi);
	ax5043_write8(AX5043_TMGRXPREAMBLE2 ,                              			0x17,spi);
	ax5043_write8(AX5043_RSSIABSTHR     ,                              			0xEB,spi);
	ax5043_write8(AX5043_BGNDRSSITHR    ,                              			0x00,spi);
	ax5043_write8(AX5043_PKTCHUNKSIZE   ,                              			0x0D,spi);
	ax5043_write8(AX5043_PKTACCEPTFLAGS ,                              			0x20,spi);
	// ax5043_write8(AX5043_DACVALUE1      ,                              			0x00,spi);
	// ax5043_write8(AX5043_DACVALUE0      ,                              			0x00,spi);
	ax5043_write8(AX5043_DACCONFIG      ,                              			0x00,spi);
	ax5043_write8(AX5043_REF            ,                              			0x03,spi);
	ax5043_write8(AX5043_XTALOSC        ,                              			0x04,spi);
	ax5043_write8(AX5043_XTALAMPL       ,                              			0x00,spi);
	ax5043_write8(AX5043_0xF1C          ,                              			0x07,spi);
	ax5043_write8(AX5043_0xF21          ,                              			0x68,spi);
	ax5043_write8(AX5043_0xF22          ,                              			0xFF,spi);
	// ax5043_write8(AX5043_0xF23          ,                              			0x84,spi);
	ax5043_write8(AX5043_0xF26          ,                              			0x98,spi);
	ax5043_write8(AX5043_0xF34          ,                              			0x28,spi);
	ax5043_write8(AX5043_0xF35          ,                              			0x11,spi);
	ax5043_write8(AX5043_0xF44          ,                              			0x25,spi);

	autorange_registers(spi);

}

void autorange_registers(SPI_TypeDef* spi){
	ax5043_write8(AX5043_XTALOSC        ,                              			0x04, spi);
	ax5043_write8(AX5043_XTALAMPL       ,                              			0x00, spi);
	ax5043_write8(AX5043_0xF34          ,                              			0x28, spi);
	ax5043_write8(AX5043_0xF35          ,                              			0x11, spi);
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x04, spi);
}

void ax5043_set_registers_tx(SPI_TypeDef* spi)
{
	ax5043_write8(AX5043_PLLLOOP        ,                              			0x09,spi);
	ax5043_write8(AX5043_PLLCPI         ,                              			30,spi); //0x02
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x24,spi);
	ax5043_write8(AX5043_XTALCAP        ,                              			0x00,spi);
	ax5043_write8(AX5043_0xF00          ,                              			0x0F,spi);
	ax5043_write8(AX5043_0xF18          ,                              			0x06,spi);

	ax5043_write8(AX5043_DIVERSITY		, 										0x00, spi);

	ax5043_write8(AX5043_FSKDEV2        ,                              			0x00,spi);
	ax5043_write8(AX5043_FSKDEV1        ,                              			0x4E,spi);
	ax5043_write8(AX5043_FSKDEV0        ,                              			0xC5,spi);
	ax5043_write8(AX5043_MODULATION     ,                              			0x07,spi); 

	ax5043_write8(AX5043_TXRATE2        ,                              			0x01,spi);
	ax5043_write8(AX5043_TXRATE1        ,                              			0x3B,spi);
	ax5043_write8(AX5043_TXRATE0        ,                              			0x14,spi);
	ax5043_write8(AX5043_TXPWRCOEFFB1   ,                              			0x10,spi);//07 originally, then 0A
	ax5043_write8(AX5043_TXPWRCOEFFB0   ,                              			0x00,spi);
	ax5043_write8(AX5043_MODCFGF        ,                              			0x02,spi);//0x03 = gaussian = 0.5
	ax5043_write8(AX5043_MODCFGA        ,                              			0x05,spi);


}


void ax5043_set_registers_rx(SPI_TypeDef* spi) 
{
	ax5043_write8(AX5043_PLLLOOP        ,                              			0x09, spi);
	ax5043_write8(AX5043_PLLCPI         ,                              			0x01, spi);
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x24, spi);
	ax5043_write8(AX5043_XTALCAP        ,                              			0x00, spi);
	ax5043_write8(AX5043_0xF00          ,                              			0x0F, spi);
	ax5043_write8(AX5043_0xF18          ,                              			0x02, spi);
}


void ax5043_set_registers_rxwor(SPI_TypeDef* spi)
{
	ax5043_write8(AX5043_TMGRXAGC,                 0x00, spi);
	ax5043_write8(AX5043_TMGRXPREAMBLE1,           0x19, spi);
	ax5043_write8(AX5043_PKTMISCFLAGS,             0x03, spi);
}

void uhf_init() {

    gpio_low(GPIOB , 9); // Disable power to UHF Transceiver 
    nop(10000000);
    gpio_high(GPIOB, 9); // Enable power to UHF Transceiver
    //power cycle the chip to clear previous auto ranges
    nop(10000000);

    spi_startCommunication(UHF_SPI_CS);

    while(!gpio_read(GPIOA, 6)); //Wait for MISO to go HIGH 

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_RST, UHF_SPI); //Turn on RST bit
  	nop(1000);
    ax5043_write8(AX5043_PWRMODE,  AX5043_PWRMODE_POWERDOWN | AX5043_PWRMODE_DEFAULTVALUES, UHF_SPI); //Turn off RST bit

    // uhf_programParametersFromRadioLab(UHF_SPI); //TODO: Get those parameters
	// wor_config(WAKEUP_FREQUENCY, UHF_SPI);
	autorange_registers(SPI1);
    int failCount = 0;
    while(!radio_autorange(AX5043_CARRIER_HZ, AX5043_XTAL_HZ, UHF_SPI)) {
        if (failCount > 3) {
            break;
        }
        failCount++;
    }
	
}

void vhf_init() {

    gpio_low(GPIOA , 8); // Disable power to UHF Transceiver 
    nop(10000);
    gpio_high(GPIOA, 8); // Enable power to UHF Transceiver
    //power cycle the chip to clear previous auto ranges
    nop(10000);

    spi_startCommunication(VHF_SPI_CS);

    while(!gpio_read(GPIOB, 14)); //Wait for MISO to go HIGH 

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_RST, VHF_SPI); //Turn on RST bit
  	nop(1000);
    ax5043_write8(AX5043_PWRMODE,  AX5043_PWRMODE_POWERDOWN | AX5043_PWRMODE_DEFAULTVALUES, VHF_SPI); //Turn off RST bit

    uhf_programParametersFromRadioLab(VHF_SPI); //TODO: Get those parameters
	// wor_config(WAKEUP_FREQUENCY, VHF_SPI);
	
    int failCount = 0;
    while(!radio_autorange(AX5043_CARRIER_HZ, AX5043_XTAL_HZ, VHF_SPI)) {
        if (failCount > 3) {
            break;
        }
        failCount++;
    }
	

}

void wor_config(int ms, SPI_TypeDef* spi){
	//check frequency of low power oscillator
	int oscillator = (ax5043_read8(AX5043_LPOSCCONFIG, spi) >> 1) & 1;
	if(oscillator){
		oscillator = 10240; //10.24kHz
	}else{
		oscillator = 640; //640Hz
	}
	//get value to put in wakeupfreq, which is # of oscillator cycles
	//frequency * period = # cycles
	uint16_t freq = ms * 1000 * oscillator; 
	ax5043_write8(AX5043_WAKEUPFREQ0, freq & 0xFF, spi);
	ax5043_write8(AX5043_WAKEUPFREQ1, freq >> 8, spi);

	//make sure receiver still on after waking up if packet received to read
	ax5043_write8(AX5043_PKTMISCFLAGS, AX5043_PKTMISCFLAGS_WORPKT, spi);

	//enable irq interrupt
	ax5043_write8(AX5043_IRQMASK0, AX5043_IRQM_FIFONOTEMPTY, spi);

}

bool radio_autorange(float carrierHz, int xtalHz, SPI_TypeDef* spi) {

	//int dac = ax5043_read8(AX5043_DACVALUE1) << 8 + ax5043_read8(AX5043_DACVALUE0) ;
	
    uint8_t printRegister = 0;

	 uint64_t freqa = (uint64_t)(carrierHz / xtalHz * (1<<24) +.5) |1;

	ax5043_write8(AX5043_FREQA0, (freqa >> 0) & 0xFF, spi);
	ax5043_write8(AX5043_FREQA1, (freqa >> 8) & 0xFF, spi);
	ax5043_write8(AX5043_FREQA2, (freqa >> 16) & 0xFF, spi);
	ax5043_write8(AX5043_FREQA3, (freqa >> 24) & 0xFF, spi);
	
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_STANDBY | AX5043_PWRMODE_DEFAULTVALUES , spi); // Set to STANDBY
	gpio_high(GPIOC, 9); //Enable clock for crystal

	while(!ax5043_read8(AX5043_XTALSTATUS, spi)); //Wait for crystal to be ready
    
	ax5043_write8(AX5043_PLLRANGINGA, AX5043_PLLRANGINGA_VCORA | AX5043_PLLRANGINGA_RNGSTART, spi); // start ranging 

	while (!(ax5043_read8(AX5043_IRQREQUEST1, spi) & 0x10)); // Check for Error

    while((ax5043_read8(AX5043_PLLRANGINGA, spi) & (AX5043_PLLRANGINGA_RNGSTART))); //Wait for RNGSTART to read 0 indicating it is done

    printRegister = ax5043_read8(AX5043_PLLRANGINGA, spi);

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN | AX5043_PWRMODE_DEFAULTVALUES, spi);

	gpio_low(GPIOC, 9); //Disable clock for crystal

    if (ax5043_read8(AX5043_PLLRANGINGA, spi) & AX5043_PLLRANGINGA_RNGERR) {
    	return false; //Indicates an error in auto ranging, try again
    }

    return true;
}

void tx_black_magic(SPI_TypeDef* spi) {
	ax5043_set_registers_tx(spi);
	// ax5043_write8(AX5043_MODULATION     ,                              			0x07,spi);
	// ax5043_write8(AX5043_TXRATE2        ,                              			0x01,spi);
	// ax5043_write8(AX5043_TXRATE1        ,                              			0x3B,spi);
	// ax5043_write8(AX5043_TXRATE0        ,                              			0x14,spi);

	// ax5043_write8(AX5043_FSKDEV2        ,                              			0x00,spi);
	// ax5043_write8(AX5043_FSKDEV1        ,                              			0x4E,spi);
	// ax5043_write8(AX5043_FSKDEV0        ,                              			0xC5,spi);

	
	// ax5043_write8(AX5043_TXPWRCOEFFB1   ,                              			0x10,spi);//7 originally
	// ax5043_write8(AX5043_TXPWRCOEFFB0   ,                              			0x00,spi);
	// ax5043_write8(AX5043_MODCFGF        ,                              			0x02,spi);//03 = gaussian = 0.5
	// ax5043_write8(AX5043_MODCFGA, 0x05, spi);


	// ax5043_write8(AX5043_ENCODING, 0x00, spi);
	// ax5043_write8(AX5043_FRAMING, 0x00, spi);
	// ax5043_write8(AX5043_PERFTUNE114, 0x06, spi);


	// ax5043_write8(AX5043_PKTLENCFG, 0xF0, spi);
	// ax5043_write8(AX5043_PKTMAXLEN, 0xFF, spi);
	// // ax5043_write8(AX5043_PKTACCEPTFLAGS, 0x20, spi);
	// ax5043_write8(AX5043_PKTCHUNKSIZE, 0x0D, spi);

	gpio_high(GPIOC, 9); //enable tcxo
	nop(1000);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX | AX5043_PWRMODE_DEFAULTVALUES, spi);
		
	int mode = ax5043_read8(AX5043_PWRMODE, spi);

    while(!(ax5043_read8(AX5043_POWSTAT, spi) & AX5043_POWSTAT_SVMODEM));//Waiting for Modem to be ready

	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS,spi);

	ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_REPEAT_DATA_COMMAND, spi);
	ax5043_write8(AX5043_FIFODATA, 0x18, spi);
	ax5043_write8(AX5043_FIFODATA, 0x14, spi);
	ax5043_write8(AX5043_FIFODATA, 0x55, spi);
	
	// ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_DATA_COMMAND, spi);
	// ax5043_write8(AX5043_FIFODATA, 101, spi);
	// ax5043_write8(AX5043_FIFODATA, 0x03, spi);

	int packetSize = 150;
	uint8_t arr[packetSize];
	for(uint8_t i = 0; i<packetSize; i++){
		arr[i] = i * 17;
	}
	while(1){
		ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_DATA_COMMAND, spi);
		ax5043_write8(AX5043_FIFODATA, packetSize + 1, spi);
		ax5043_write8(AX5043_FIFODATA, 0x03, spi);

		for(uint8_t i = 0; i<packetSize; i++){
			ax5043_write8(AX5043_FIFODATA, arr[i], spi);
		}
		
		ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT, spi);
		int radiostate =ax5043_read8(AX5043_RADIOSTATE, spi);
		while(ax5043_read8(AX5043_RADIOSTATE, spi)){
			radiostate = ax5043_read8(AX5043_RADIOSTATE, spi); 
		}
	}
	
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);//set to powerdowm
	gpio_low(GPIOC, 9); //disable txco
}


void tx_simple(SPI_TypeDef* spi){
	ax5043_set_registers_tx(spi);
	int radiostate = -1;
	gpio_high(GPIOC, 9); //enable tcxo
	nop(1000);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX | AX5043_PWRMODE_DEFAULTVALUES, spi);

    while(!(ax5043_read8(AX5043_POWSTAT, spi) & AX5043_POWSTAT_SVMODEM));//Waiting for Modem to be ready

	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS,spi);
	int free = ax5043_read8(AX5043_FIFOFREE1, spi) << 8| ax5043_read8(AX5043_FIFOFREE0, spi);

	while(1){
		ax5043_write8(AX5043_FIFODATA, 0xE1, spi);
		ax5043_write8(AX5043_FIFODATA, 0x04, spi);
		ax5043_write8(AX5043_FIFODATA, 0x27, spi);
		ax5043_write8(AX5043_FIFODATA, 0xAA, spi);
		ax5043_write8(AX5043_FIFODATA, 0xAA, spi);
		ax5043_write8(AX5043_FIFODATA, 0x1A, spi);


		ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT, spi);
		radiostate = ax5043_read8(AX5043_RADIOSTATE, spi);


		//Wait for transmitting to be active by making sure it changes from IDLE and that FIFO is being filled
		free = ax5043_read8(AX5043_FIFOFREE1, spi) << 8| ax5043_read8(AX5043_FIFOFREE0, spi);
		while(!ax5043_read8(AX5043_RADIOSTATE, spi) && ((ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi) < 10));
				
		int fifosize = -1;
		int fifostat = -1;
		while(ax5043_read8(AX5043_RADIOSTATE, spi));
	}
	ax5043_write8(AX5043_FIFODATA, 0xE1, spi);
	ax5043_write8(AX5043_FIFODATA, 0x04, spi);
	ax5043_write8(AX5043_FIFODATA, 0x27, spi);
	ax5043_write8(AX5043_FIFODATA, 0xAA, spi);
	ax5043_write8(AX5043_FIFODATA, 0xAA, spi);
	ax5043_write8(AX5043_FIFODATA, 0x1A, spi);


	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT, spi);
	radiostate = ax5043_read8(AX5043_RADIOSTATE, spi);


	//Wait for transmitting to be active by making sure it changes from IDLE and that FIFO is being filled
	free = ax5043_read8(AX5043_FIFOFREE1, spi) << 8| ax5043_read8(AX5043_FIFOFREE0, spi);
	while(!ax5043_read8(AX5043_RADIOSTATE, spi) && ((ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi) < 10));
			
	int fifosize = -1;
	int fifostat = -1;
	while(ax5043_read8(AX5043_RADIOSTATE, spi)){
		radiostate = ax5043_read8(AX5043_RADIOSTATE, spi); //Wait for RadioState to show IDLE
		// fifo = ax5043_read8(AX5043_FIFODATA, spi);
		fifosize = (ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi); 
		fifostat = ax5043_read8(AX5043_FIFOSTAT, spi);
	}
	radiostate = ax5043_read8(AX5043_RADIOSTATE, spi);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);//set to powerdowm
	gpio_low(GPIOC, 9); //disable txco


}

void radio_transmit(int numBytes, uint8_t* bytesToSend, SPI_TypeDef* spi) {
    ax5043_set_registers_tx(spi);
    int bytesSent = 0;
    int pktCurrentIndex = 0;
    int packetSize = 0; 
    int spaceLeftInFIFO = 0;
    
    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX | AX5043_PWRMODE_DEFAULTVALUES, spi);
    while(!(ax5043_read8(AX5043_POWSTAT, spi) & AX5043_POWSTAT_SVMODEM)); //Waiting for Modem to be ready
	gpio_high(GPIOC, 9); //enable tcxo


	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS,spi); //clear data from fifo
	
	//write preamble
	ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_REPEAT_DATA_COMMAND, spi);
	ax5043_write8(AX5043_FIFODATA, AX5043_TX_FLAGS_UNENC | AX5043_TX_FLAGS_NOCRC, spi); //no crc and bypass framing + encoding
	ax5043_write8(AX5043_FIFODATA, 34, spi); //32 bits originally, going to try 272
	ax5043_write8(AX5043_FIFODATA, 0xAA, spi);
	
	while (bytesSent < numBytes) {
		spaceLeftInFIFO = (ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi); 

		if (spaceLeftInFIFO > numBytes + 3 - bytesSent) { //Adding three bytes for Header Byte, Length Byte, and Flag Byte
			packetSize = numBytes + 3 - bytesSent;
		} else {
			packetSize = spaceLeftInFIFO;
		}

		uint8_t length = packetSize - 2; //Subtracting two to account for header and length byte
		ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_DATA_COMMAND, spi); //Header byte indicating DATA command
		ax5043_write8(AX5043_FIFODATA, length, spi);

		uint8_t flags = 0;

		if (pktCurrentIndex == 0) {
			flags |= AX5043_TX_FLAGS_PKTSTART;
		}

		//If the amount of bytes about to be sent is equal or more than numBytes than must have end of packet
		if (pktCurrentIndex + length >= numBytes) {
			flags |= AX5043_TX_FLAGS_PKTEND;
		}

		ax5043_write8(AX5043_FIFODATA, flags, spi);
		length--; 

		int sent = 0;
		while(pktCurrentIndex < length){
			ax5043_write8(AX5043_FIFODATA, bytesToSend[pktCurrentIndex], spi);
			sent++;
			pktCurrentIndex ++;
		}
		//ax5043_write8(AX5043_FIFODATA, 'K'); //send minimum amount


		//check if crytal is running
		while(!ax5043_read8(AX5043_XTALSTATUS, spi));

		ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT, spi);

		//Wait for transmitting to be active by making sure it changes from IDLE and that FIFO is being filled
		while(!ax5043_read8(AX5043_RADIOSTATE, spi) && ((ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi) < 10));
		

		bytesSent += packetSize - 3;
		int radiostate = -1;
		int fifo = -1;
		int fifosize = -1;
		int fifostat = -1;
		while(ax5043_read8(AX5043_RADIOSTATE, spi)){
			radiostate = ax5043_read8(AX5043_RADIOSTATE, spi); //Wait for RadioState to show IDLE
			fifo = ax5043_read8(AX5043_FIFODATA, spi);
			fifosize = (ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi); 
			fifostat = ax5043_read8(AX5043_FIFOSTAT, spi);
		}

	}
	
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);//set to powerdowm
	gpio_low(GPIOC, 9); //disable txco

}
 
 
bool radio_receive(packet_t* received_packet, SPI_TypeDef* spi) {
	ax5043_set_registers_rx(spi);
	if (ax5043_read8(AX5043_FIFOCOUNT0, spi) > 0) {

		ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLRX, spi); //worrx for wor and fullrx for regular
		gpio_high(GPIOC, 9);

		uint8_t header = ax5043_read8(AX5043_FIFODATA, spi);
		uint8_t length = ax5043_read8(AX5043_FIFODATA, spi);
		uint8_t flags = ax5043_read8(AX5043_FIFODATA, spi);
		received_packet->isPacketStart = flags & AX5043_TX_FLAGS_PKTSTART;
		received_packet->isPacketEnd = flags & AX5043_TX_FLAGS_PKTEND;
		received_packet->length = length - 1;
		
		for (int i = 0; i < length - 1; i++) {
			if (header == AX5043_FIFODATA_DATA_COMMAND) { //Only read it if its a data command 
				(received_packet->pkt)[i] = ax5043_read8(AX5043_FIFODATA, spi);
			}
		}

		ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);
		gpio_low(GPIOC, 9);
		
		return true;
	}

	return false; 
} 

uint8_t ax5043_read8(uint32_t address, SPI_TypeDef* spi) {
    uint8_t addr[2];
    addr[0] = address >> 8;
    addr[0] |=  0xF0;   // Set left 4 bits to 0b1111
    addr[0] &= (uint8_t) ~0x80;   // Clear left most bit

    addr[1] = address &= 0x00FF;    // 8 rightmost bits go to addr[1]
    
    uint8_t discard[2] = {0xFF, 0xFF};
    uint8_t regVal[1] = {0xFF};

	if(spi == SPI1){
		spi_startCommunication(UHF_SPI_CS);
	}else {
		spi_startCommunication(VHF_SPI_CS);
	}
    

    while (spi->SR & SPI_SR_RXNE) {	// CLear RX Fifo
    	spi->DR;
	}

    spi_transmitReceive(spi, addr, discard, 2, false);
    spi_transmitReceive(spi, NULL, regVal, 1, false);

	if(spi == SPI1){
		spi_stopCommunication(UHF_SPI_CS);
	}else {
		spi_stopCommunication(VHF_SPI_CS);
	}

    return regVal[0];
}

void ax5043_write8(uint8_t address, uint8_t data, SPI_TypeDef* spi) {
    uint8_t spiDATA[2];
	spiDATA[0] = (uint8_t)address | 0x80;
	spiDATA[1] = data;


	if(spi == SPI1){
		spi_startCommunication(UHF_SPI_CS);
	}else {
		spi_startCommunication(VHF_SPI_CS);
	}   
	
	spi_transmitReceive(spi, &spiDATA, NULL, 2, false);

	if(spi == SPI1){
		spi_stopCommunication(UHF_SPI_CS);
	}else {
		spi_stopCommunication(VHF_SPI_CS);
	}

    int test = 33;
}

