#include "AX5043.h"
#include <print_scan.h>

void radio_init() {
    spi_config(UHF_SPI);
	spi_config(VHF_SPI);
    uhf_init();
	ax5043_configInterrupt(); //setup recieve interrupt

}

void uhf_programParametersFromRadioLab(SPI_TypeDef* spi) {

	ax5043_write8(AX5043_MODULATION     ,                              			0x07, spi);
	ax5043_write8(AX5043_ENCODING       ,                              			0x03, spi);
	ax5043_write8(AX5043_FRAMING        ,                              			0x64, spi);
	ax5043_write8(AX5043_PINFUNCSYSCLK  ,                              			0x01, spi);
	ax5043_write8(AX5043_PINFUNCDCLK    ,                              			0x01, spi);
	ax5043_write8(AX5043_PINFUNCDATA    ,                              			0x01, spi);
	ax5043_write8(AX5043_PINFUNCANTSEL  ,                              			0x01, spi);
	ax5043_write8(AX5043_PINFUNCPWRAMP  ,                              			0x07, spi);
	ax5043_write8(AX5043_WAKEUPXOEARLY  ,                              			0x01, spi);
	ax5043_write8(AX5043_IFFREQ1        ,                              			0x0F, spi);
	ax5043_write8(AX5043_IFFREQ0        ,                              			0xC1, spi);
	ax5043_write8(AX5043_DECIMATION     ,                              			0x02, spi);
	ax5043_write8(AX5043_RXDATARATE2    ,                              			0x00, spi);
	ax5043_write8(AX5043_RXDATARATE1    ,                              			0x43, spi);
	ax5043_write8(AX5043_RXDATARATE0    ,                              			0xB5, spi);
	ax5043_write8(AX5043_MAXDROFFSET2   ,                              			0x00, spi);
	ax5043_write8(AX5043_MAXDROFFSET1   ,                              			0x00, spi);
	ax5043_write8(AX5043_MAXDROFFSET0   ,                              			0x00, spi);
	ax5043_write8(AX5043_MAXRFOFFSET2   ,                              			0x80, spi);
	ax5043_write8(AX5043_MAXRFOFFSET1   ,                              			0x00, spi);
	ax5043_write8(AX5043_MAXRFOFFSET0   ,                              			0x00, spi);
	ax5043_write8(AX5043_AMPLFILTER     ,                              			0x00, spi);
	ax5043_write8(AX5043_RXPARAMSETS    ,                              			0xF4, spi);
	ax5043_write8(AX5043_AGCGAIN0       ,                              			0x93, spi);
	ax5043_write8(AX5043_AGCTARGET0     ,                              			0x84, spi);
	ax5043_write8(AX5043_TIMEGAIN0      ,                              			0x89, spi);
	ax5043_write8(AX5043_DRGAIN0        ,                              			0x83, spi);
	ax5043_write8(AX5043_PHASEGAIN0     ,                              			0xC3, spi);
	ax5043_write8(AX5043_FREQUENCYGAINA0,                              			0x26, spi);
	ax5043_write8(AX5043_FREQUENCYGAINB0,                              			0x0A, spi);
	ax5043_write8(AX5043_FREQUENCYGAINC0,                              			0x1F, spi);
	ax5043_write8(AX5043_FREQUENCYGAIND0,                              			0x1F, spi);
	ax5043_write8(AX5043_AMPLITUDEGAIN0 ,                              			0x06, spi);
	ax5043_write8(AX5043_FREQDEV10      ,                              			0x00, spi);
	ax5043_write8(AX5043_FREQDEV00      ,                              			0x00, spi);
	ax5043_write8(AX5043_BBOFFSRES0     ,                              			0x00, spi);
	ax5043_write8(AX5043_AGCGAIN1       ,                              			0x93, spi);
	ax5043_write8(AX5043_AGCTARGET1     ,                              			0x84, spi);
	ax5043_write8(AX5043_AGCAHYST1      ,                              			0x00, spi);
	ax5043_write8(AX5043_AGCMINMAX1     ,                              			0x00, spi);
	ax5043_write8(AX5043_TIMEGAIN1      ,                              			0x87, spi);
	ax5043_write8(AX5043_DRGAIN1        ,                              			0x82, spi);
	ax5043_write8(AX5043_PHASEGAIN1     ,                              			0xC3, spi);
	ax5043_write8(AX5043_FREQUENCYGAINA1,                              			0x26, spi);
	ax5043_write8(AX5043_FREQUENCYGAINB1,                              			0x0A, spi);
	ax5043_write8(AX5043_FREQUENCYGAINC1,                              			0x1F, spi);
	ax5043_write8(AX5043_FREQUENCYGAIND1,                              			0x1F, spi);
	ax5043_write8(AX5043_AMPLITUDEGAIN1 ,                              			0x06, spi);
	ax5043_write8(AX5043_FREQDEV11      ,                              			0x00, spi);
	ax5043_write8(AX5043_FREQDEV01      ,                              			0x2D, spi);
	ax5043_write8(AX5043_FOURFSK1       ,                              			0x16, spi);
	ax5043_write8(AX5043_BBOFFSRES1     ,                              			0x00, spi);
	ax5043_write8(AX5043_AGCGAIN3       ,                              			0xFF, spi);
	ax5043_write8(AX5043_AGCTARGET3     ,                              			0x84, spi);
	ax5043_write8(AX5043_AGCAHYST3      ,                              			0x00, spi);
	ax5043_write8(AX5043_AGCMINMAX3     ,                              			0x00, spi);
	ax5043_write8(AX5043_TIMEGAIN3      ,                              			0x86, spi);
	ax5043_write8(AX5043_DRGAIN3        ,                              			0x81, spi);
	ax5043_write8(AX5043_PHASEGAIN3     ,                              			0xC3, spi);
	ax5043_write8(AX5043_FREQUENCYGAINA3,                              			0x26, spi);
	ax5043_write8(AX5043_FREQUENCYGAINB3,                              			0x0A, spi);
	ax5043_write8(AX5043_FREQUENCYGAINC3,                              			0x1F, spi);
	ax5043_write8(AX5043_FREQUENCYGAIND3,                              			0x1F, spi);
	ax5043_write8(AX5043_AMPLITUDEGAIN3 ,                              			0x06, spi);
	ax5043_write8(AX5043_FREQDEV13      ,                              			0x00, spi);
	ax5043_write8(AX5043_FREQDEV03      ,                              			0x2D, spi);
	ax5043_write8(AX5043_FOURFSK3       ,                              			0x16, spi);
	ax5043_write8(AX5043_BBOFFSRES3     ,                              			0x00, spi);
	ax5043_write8(AX5043_MODCFGF        ,                              			0x03, spi);
	ax5043_write8(AX5043_FSKDEV2        ,                              			0x00, spi);
	ax5043_write8(AX5043_FSKDEV1        ,                              			0x1E, spi);
	ax5043_write8(AX5043_FSKDEV0        ,                              			0x3F, spi);
	ax5043_write8(AX5043_MODCFGA        ,                              			0x05, spi);
	ax5043_write8(AX5043_TXRATE2        ,                              			0x00, spi);
	ax5043_write8(AX5043_TXRATE1        ,                              			0x78, spi);
	ax5043_write8(AX5043_TXRATE0        ,                              			0xFD, spi);
	ax5043_write8(AX5043_TXPWRCOEFFB1   ,                              			0x0F, spi);
	ax5043_write8(AX5043_TXPWRCOEFFB0   ,                              			0xFF, spi);
	ax5043_write8(AX5043_PLLVCOI        ,                              			0x98, spi);
	ax5043_write8(AX5043_PLLRNGCLK      ,                              			0x04, spi);
	ax5043_write8(AX5043_BBTUNE         ,                              			0x0A, spi);
	ax5043_write8(AX5043_BBOFFSCAP      ,                              			0x77, spi);
	ax5043_write8(AX5043_PKTADDRCFG     ,                              			0x80, spi);
	ax5043_write8(AX5043_PKTLENCFG      ,                              			0xF0, spi);
	ax5043_write8(AX5043_PKTLENOFFSET   ,                              			0x00, spi);
	ax5043_write8(AX5043_PKTMAXLEN      ,                              			0xFF, spi);
	ax5043_write8(AX5043_MATCH0PAT3     ,                              			0xAA, spi);
	ax5043_write8(AX5043_MATCH0PAT2     ,                              			0xCC, spi);
	ax5043_write8(AX5043_MATCH0PAT1     ,                              			0xAA, spi);
	ax5043_write8(AX5043_MATCH0PAT0     ,                              			0xCC, spi);
	ax5043_write8(AX5043_MATCH1PAT1     ,                              			0x55, spi);
	ax5043_write8(AX5043_MATCH1PAT0     ,                              			0x55, spi);
	ax5043_write8(AX5043_MATCH1LEN      ,                              			0x8A, spi);
	ax5043_write8(AX5043_MATCH1MAX      ,                              			0x05, spi);
	ax5043_write8(AX5043_TMGTXBOOST     ,                              			0x3E, spi);
	ax5043_write8(AX5043_TMGTXSETTLE    ,                              			0x31, spi);
	ax5043_write8(AX5043_TMGRXBOOST     ,                              			0x3E, spi);
	ax5043_write8(AX5043_TMGRXSETTLE    ,                              			0x31, spi);
	ax5043_write8(AX5043_TMGRXOFFSACQ   ,                              			0x00, spi);
	ax5043_write8(AX5043_TMGRXCOARSEAGC ,                              			0x7F, spi);
	ax5043_write8(AX5043_TMGRXRSSI      ,                              			0x03, spi);
	ax5043_write8(AX5043_TMGRXPREAMBLE2 ,                              			0x17, spi);
	ax5043_write8(AX5043_RSSIABSTHR     ,                              			0xE9, spi);
	ax5043_write8(AX5043_BGNDRSSITHR    ,                              			0x00, spi);
	ax5043_write8(AX5043_PKTCHUNKSIZE   ,                              			0x0D, spi);
	ax5043_write8(AX5043_PKTACCEPTFLAGS ,                              			0x31, spi);
	ax5043_write8(AX5043_DACVALUE1      ,                              			0x00, spi);
	ax5043_write8(AX5043_DACVALUE0      ,                              			0x00, spi);
	ax5043_write8(AX5043_DACCONFIG      ,                              			0x00, spi);
	ax5043_write8(AX5043_REF            ,                              			0x03, spi);
	ax5043_write8(AX5043_XTALOSC        ,                              			0x04, spi);
	ax5043_write8(AX5043_XTALAMPL       ,                              			0x00, spi);
	ax5043_write8(AX5043_0xF1C          ,                              			0x07, spi);
	ax5043_write8(AX5043_0xF21          ,                              			0x68, spi);
	ax5043_write8(AX5043_0xF22          ,                              			0xFF, spi);
	ax5043_write8(AX5043_0xF23          ,                              			0x84, spi);
	ax5043_write8(AX5043_0xF26          ,                              			0x98, spi);
	ax5043_write8(AX5043_0xF34          ,                              			0x28, spi);
	ax5043_write8(AX5043_0xF35          ,                              			0x11, spi);
	ax5043_write8(AX5043_0xF44          ,                              			0x25, spi);
	// autorange_registers(spi);

}

void autorange_registers(SPI_TypeDef* spi){
	ax5043_write8(AX5043_XTALOSC        ,                              			0x04, spi);
	ax5043_write8(AX5043_XTALAMPL       ,                              			0x00, spi);
	ax5043_write8(AX5043_0xF34          ,                              			0x28, spi);
	ax5043_write8(AX5043_0xF35          ,                              			0x11, spi); //fxtaldiv = 2
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x04, spi);
}

void ax5043_set_registers_tx(SPI_TypeDef* spi)
{
	ax5043_write8(AX5043_PWRMODE,  AX5043_PWRMODE_POWERDOWN, spi); //Turn off RST bit

	ax5043_write8(AX5043_PLLLOOP        ,                              			0x09, spi);
	ax5043_write8(AX5043_PLLCPI         ,                              			0x02, spi);
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x24, spi);
	ax5043_write8(AX5043_XTALCAP        ,                              			0x00, spi);
	ax5043_write8(AX5043_0xF00          ,                              			0x0F, spi);
	ax5043_write8(AX5043_0xF18          ,                              			0x06, spi);
	return;
}


void ax5043_set_registers_rx(SPI_TypeDef* spi) 
{

	ax5043_write8(AX5043_PLLLOOP        ,                              			0x09, spi);
	ax5043_write8(AX5043_PLLCPI         ,                              			0x01, spi);
	ax5043_write8(AX5043_PLLVCODIV      ,                              			0x24, spi);
	ax5043_write8(AX5043_XTALCAP        ,                              			0x00, spi);
	ax5043_write8(AX5043_0xF00          ,                              			0x0F, spi);
	ax5043_write8(AX5043_0xF18          ,                              			0x02, spi);
	return;
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
    uhf_programParametersFromRadioLab(UHF_SPI); //TODO: Get those parameters
	// wor_config(WAKEUP_FREQUENCY, UHF_SPI);
    int pwrmode = ax5043_read8(AX5043_PWRMODE, UHF_SPI);
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
    nop(10000000);
    gpio_high(GPIOA, 8); // Enable power to UHF Transceiver
    //power cycle the chip to clear previous auto ranges
    nop(10000000);

    spi_startCommunication(VHF_SPI_CS);

    while(!gpio_read(GPIOB, 14)); //Wait for MISO to go HIGH 

    ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_RST, VHF_SPI); //Turn on RST bit
  	nop(1000);
    ax5043_write8(AX5043_PWRMODE,  AX5043_PWRMODE_POWERDOWN | AX5043_PWRMODE_DEFAULTVALUES, VHF_SPI); //Turn off RST bit
    uhf_programParametersFromRadioLab(VHF_SPI); //TODO: Get those parameters
	// wor_config(WAKEUP_FREQUENCY, VHF_SPI);
	autorange_registers(VHF_SPI);

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

void tx_black_magic(SPI_TypeDef* spi, int packetSize) {
	ax5043_set_registers_tx(spi);
	
	//disable fifonotempty interrupt
	int irqmask = ax5043_read8(AX5043_IRQMASK0, spi);
	ax5043_write8(AX5043_IRQMASK0, irqmask & ~AX5043_IRQM_FIFONOTEMPTY, spi); 

	gpio_high(GPIOC, 9); //enable tcxo
	nop(1000);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX | AX5043_PWRMODE_DEFAULTVALUES, spi);
	
    while(!(ax5043_read8(AX5043_POWSTAT, spi) & AX5043_POWSTAT_SVMODEM));//Waiting for Modem to be ready

	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS,spi);

	ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_REPEAT_DATA_COMMAND, spi);
	ax5043_write8(AX5043_FIFODATA, AX5043_TX_FLAGS_UNENC | AX5043_TX_FLAGS_NOCRC | AX5043_TX_FLAGS_RAW, spi);
	ax5043_write8(AX5043_FIFODATA, 68, spi);
	ax5043_write8(AX5043_FIFODATA, 0xAA, spi);

	uint8_t arr[250];
	for(uint8_t i = 0; i<packetSize; i++){
		arr[i] = i * 17 + 5;
	}

		ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_DATA_COMMAND, spi);
		ax5043_write8(AX5043_FIFODATA, packetSize + 1, spi);
		ax5043_write8(AX5043_FIFODATA,  AX5043_TX_FLAGS_PKTSTART | AX5043_TX_FLAGS_PKTEND, spi);
		
		for(uint8_t i = 0; i<packetSize ; i++){
			ax5043_write8(AX5043_FIFODATA, i, spi);
		}

		ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT, spi);
		
		int radiostate =ax5043_read8(AX5043_RADIOSTATE, spi);
		while(ax5043_read8(AX5043_RADIOSTATE, spi)){
			radiostate = ax5043_read8(AX5043_RADIOSTATE, spi); 
			printMsg("RX RADIOSTATE: %d\r\n", ax5043_read8(AX5043_RADIOSTATE, UHF_SPI) );
		}

	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);//set to powerdowm
	gpio_low(GPIOC, 9); //disable txco

	//reenable irq for recieving
	ax5043_write8(AX5043_IRQMASK0, irqmask | AX5043_IRQM_FIFONOTEMPTY, spi); 

}

void radio_transmit(int numBytes, uint8_t* bytesToSend, SPI_TypeDef* spi) {
    ax5043_set_registers_tx(spi);
    int bytesSent = 0;
    int pktCurrentIndex = 0;
    int packetSize = 0; 
    int spaceLeftInFIFO = 0;
    
	int irqmask = ax5043_read8(AX5043_IRQMASK0, spi);
	ax5043_write8(AX5043_IRQMASK0, irqmask & ~AX5043_IRQM_FIFONOTEMPTY, spi); 

	gpio_high(GPIOC, 9); //enable tcxo
	nop(1000);
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLTX | AX5043_PWRMODE_DEFAULTVALUES, spi);
	
    while(!(ax5043_read8(AX5043_POWSTAT, spi) & AX5043_POWSTAT_SVMODEM));//Waiting for Modem to be ready
	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS,spi);

	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS,spi);
		ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_REPEAT_DATA_COMMAND, spi);
		ax5043_write8(AX5043_FIFODATA, AX5043_TX_FLAGS_UNENC | AX5043_TX_FLAGS_NOCRC | AX5043_TX_FLAGS_RAW, spi);
		ax5043_write8(AX5043_FIFODATA, 68, spi);
		ax5043_write8(AX5043_FIFODATA, 0xAA, spi);
	int count = 0;
	while(bytesSent < numBytes){
		spaceLeftInFIFO = (ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi); 
		while(spaceLeftInFIFO < 4){
			spaceLeftInFIFO = (ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi); 
		}
		if (spaceLeftInFIFO > numBytes - bytesSent + 3) { //Adding three bytes for Header Byte, Length Byte, and Flag Byte
			packetSize = numBytes + 3 - bytesSent;
		} else {
			packetSize = spaceLeftInFIFO;
		}
		
		uint8_t length = packetSize - 2; //Subtracting two to account for header and length byte
		ax5043_write8(AX5043_FIFODATA, AX5043_FIFODATA_DATA_COMMAND, spi); //Header byte indicating DATA command
		ax5043_write8(AX5043_FIFODATA, length--, spi);
		uint8_t flags = 0;
		if(bytesSent == 0){
			flags = AX5043_TX_FLAGS_PKTSTART;
		}
		if(bytesSent + length >= numBytes){
			flags |= AX5043_TX_FLAGS_PKTEND;
		}
		ax5043_write8(AX5043_FIFODATA, flags, spi);

		int sent = 0;
		while(sent < length){
			ax5043_write8(AX5043_FIFODATA, bytesToSend[bytesSent + sent], spi);
			sent++;
		}

		//check if crytal is running
		while(!ax5043_read8(AX5043_XTALSTATUS, spi));

		ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_COMMIT, spi);
		//Wait for transmitting to be active by making sure it changes from IDLE and that FIFO is being filled
		// while(!ax5043_read8(AX5043_RADIOSTATE, spi) && ((ax5043_read8(AX5043_FIFOFREE1, spi) << 8) | ax5043_read8(AX5043_FIFOFREE0, spi) < 10));
		

		bytesSent += sent;
		printMsg("transmission %d, bytesSent = %d\r\n", count++, bytesSent);
		// delay_ms(1000);
	}	
	while(ax5043_read8(AX5043_RADIOSTATE, spi));
	
	ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);//set to powerdown
	ax5043_write8(AX5043_IRQMASK0, irqmask | AX5043_IRQM_FIFONOTEMPTY, spi); 
	gpio_low(GPIOC, 9); //disable txco

}
 
 
int radio_receive(packet_t* received_packet, SPI_TypeDef* spi) {
//	ax5043_set_registers_rx(spi);

	
	// ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_FULLRX, spi); //worrx for wor and fullrx for regular
	// gpio_high(GPIOC, 9);
	int received = 0;
	int fifocount = ax5043_read8(AX5043_FIFOCOUNT0, spi) | ax5043_read8(AX5043_FIFOCOUNT1, spi) << 8;
	// printMsg("FIFOCOUNT: %d\r\n", fifocount);
	if(fifocount == 0){
		return -1;
	}
		uint8_t header = ax5043_read8(AX5043_FIFODATA, spi);
		if (header != AX5043_FIFODATA_DATA_COMMAND){
			return -1;
		}
		uint8_t length = ax5043_read8(AX5043_FIFODATA, spi);
		uint8_t flags = ax5043_read8(AX5043_FIFODATA, spi);
		received_packet->isPacketStart = flags & AX5043_TX_FLAGS_PKTSTART;
		received_packet->isPacketEnd = flags & AX5043_TX_FLAGS_PKTEND;
		received_packet->length = length - 1;
		printMsg("HEADER: %x\r\n", header);
		printMsg("LENGTH: %d\r\n", length-1);
		printMsg("FLAGS: %x\r\n", flags);
		for (int i = 0; i < length - 1; i++) {
			// if (header == AX5043_FIFODATA_DATA_COMMAND) { //Only read it if its a data command
				(received_packet->pkt)[i] = ax5043_read8(AX5043_FIFODATA, spi);
			// }
		}
	// }

	// ax5043_write8(AX5043_PWRMODE, AX5043_PWRMODE_POWERDOWN, spi);
	// gpio_low(GPIOC, 9);

	return length-1;
} 

uint8_t ax5043_read8(uint16_t address, SPI_TypeDef* spi) {
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

void ax5043_write8(uint16_t address, uint8_t data, SPI_TypeDef* spi) {
    uint8_t spiDATA[3];
	int size = 2;
	if(address & 0xF00){//if longer than 8 bits
		size = 3;
		spiDATA[0] = (address >> 8) | 0xF0;
		spiDATA[1] = address & 0xFF; 
		spiDATA[2] = data;
	}else{
		spiDATA[0] = (uint16_t)address | 0x80;
		spiDATA[1] = data;
	}
	


	if(spi == SPI1){
		spi_startCommunication(UHF_SPI_CS);
	}else {
		spi_startCommunication(VHF_SPI_CS);
	}   
	
	spi_transmitReceive(spi, &spiDATA, NULL, size, false);

	if(spi == SPI1){
		spi_stopCommunication(UHF_SPI_CS);
	}else {
		spi_stopCommunication(VHF_SPI_CS);
	}

    int test = 33;
}

void ax5043_configInterrupt(){

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //enable syscfg

	//IRQ = PA2
	GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;	//input mode 00
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->RTSR1|= EXTI_RTSR1_RT2;
	EXTI->FTSR1|= EXTI_FTSR1_FT2;
	 NVIC_EnableIRQ(EXTI2_IRQn);

	//IRQ = PB11
	GPIOB->MODER &= ~GPIO_MODER_MODE11_Msk;
	SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI11;
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI11_PB;
	EXTI->IMR1 |= EXTI_IMR1_IM11;
	EXTI->RTSR1 |= EXTI_RTSR1_RT11;
	EXTI->FTSR1 |= EXTI_FTSR1_FT11;
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, SPI1);
	ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, SPI2);

	ax5043_write8(AX5043_IRQMASK0, AX5043_IRQM_FIFONOTEMPTY, SPI1);
	ax5043_write8(AX5043_IRQMASK0, AX5043_IRQM_FIFONOTEMPTY, SPI2);
}

void EXTI2_IRQHandler(){
	printMsg("INTERRUPT on UHF!\r\n");
	NVIC_DisableIRQ(EXTI2_IRQn);
	EXTI->PR1 |= EXTI_PR1_PIF2;
	packet_t packet;
	for(int i = 0; i<256; i++){
		packet.pkt[i] = 0;
	}
	int size = 0;
	char arr[1000];
	for(int i = 0; i<1000; i++){
		arr[i] = 0;
	}
	int count = 0;
	do{
		printMsg("Received: %d\r\n", count);
		size = radio_receive(&packet, UHF_SPI);
		// printMsg("size: %d\r\n", size);
		for(int i = 0; i<size; i++){
			arr[count + i] = packet.pkt[i];
		}
		if(size > 0)
			count += size;
	}while(count < 1000 && !packet.isPacketEnd);
	for(int i = 0; i< 1000; i++){
		printMsg("%c", arr[i]);
	}
	// printMsg("\r\n");
	// ax5043_write8(AX5043_FIFOSTAT, AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS, UHF_SPI);
	// printMsg("FINISH INTERRUPT\r\n");
	NVIC_EnableIRQ(EXTI2_IRQn);
}

void EXTI15_10_IRQHandler(){
	printMsg("INTERRUPT on VHF!\r\n");
	EXTI->PR1 |= EXTI_PR1_PIF11;
}
