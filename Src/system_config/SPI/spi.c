/*
 * spi.c
 *
 *	- August 17, 2024
 *		Author	: Darsh
 *		Log		: Copied from IntelliSat
 */

#include "spi.h"

/**
 * Configures GPIO for the SPI-2 Peripheral
 */
void spi3_gpioInit() {

}


void spi2_gpioInit() {
/**
 * VHF Transceiver
 */
}

void spi1_gpioInit() {
/**
 * UHF Transceiver 
 * 		CS		A3		
 * 		CLK		A5		AF5
 * 		MISO	A6 		AF5
 * 		MOSI 	A7		AF5
 * 	
 */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	while (GPIOA->OTYPER == 0xFFFFFFFF);

	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;

	GPIOA->MODER &= ~(
			GPIO_MODER_MODE3_Msk
			| GPIO_MODER_MODE5_Msk
			| GPIO_MODER_MODE6_Msk
			| GPIO_MODER_MODE7_Msk);
	GPIOA->MODER |=
		  GPIO_MODER_MODE3_0
		| GPIO_MODER_MODE5_1
		| GPIO_MODER_MODE6_1
		| GPIO_MODER_MODE7_1;

	GPIOA->AFR[0] &= ~(
		  GPIO_AFRL_AFSEL5_Msk
		| GPIO_AFRL_AFSEL6_Msk
		| GPIO_AFRL_AFSEL7_Msk);

	GPIOA->AFR[0] |=
		  5U << GPIO_AFRL_AFSEL5_Pos
		| 5U << GPIO_AFRL_AFSEL6_Pos
		| 5U << GPIO_AFRL_AFSEL7_Pos;


}

/**************************** SPI INITIALIZATIONS ****************************/

void spi_disable(SPI_TypeDef *spi, GPIO_TypeDef *cs_port, int cs_pin) {
	while(spi->SR & SPI_SR_FTLVL);	// Wait till there is no data to transmit
	while(spi->SR & SPI_SR_BSY);	// Wait till last data frame is processed
	spi_stopCommunication(cs_port, cs_pin);
	spi->CR1 &= ~SPI_CR1_SPE;		// Disable SPI2

	uint8_t temp;
	while(spi->SR & SPI_SR_FRLVL){
		// Wait till all data is received
		temp = SPI2->DR;
	}
}

void spi1_config() {
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;	// GPIO
	spi1_gpioInit();

	spi_disable(SPI1, SPI1_CS);

	SPI1->CR1 = 0;
	SPI1->CR2 = 0;
	// CR1
	SPI1->CR1 |=
		 5U << SPI_CR1_BR_Pos		// Baud Rate of `Clock_Source/64` (78.125 KHz)
		| SPI_CR1_SSM				// (CS is controlled by software)
		| SPI_CR1_SSI				// (CS is controlled by software)
		| SPI_CR1_MSTR;
	// CR2
	SPI2->CR2 |=
		  SPI_CR2_FRXTH			// RXNE generated when RXFIFO has 1 byte
		| 7U << SPI_CR2_DS_Pos; // Transfer Data Length is 1 Byte
	spi_enable(SPI1);

}

void spi2_config() {
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;	// Clock
	spi2_gpioInit();						// GPIO

	spi_disable(SPI2, SPI2_CS);

	SPI2->CR1 = 0;
	SPI2->CR2 = 0;
	// CR1
	// CR2

	spi_enable(SPI2);
}

void spi3_config() {
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN;	// Clock
    spi3_gpioInit();						// GPIO

	spi_disable(SPI3, SPI3_CS);

	SPI3->CR1 = 0;
	SPI3->CR2 = 0;
	// CR1
	// CR2

	spi_enable(SPI3);
}

void spi_config(SPI_TypeDef *spi) {
	switch ((uint32_t)spi) {
		case (uint32_t)SPI1:
			spi1_config();
			break;
		case (uint32_t)SPI2:
			spi2_config();
			break;
		case (uint32_t)SPI3:
			spi3_config();
			break;
	}
}

/***************************** SPI COMMUNICATION *****************************/
void spi_startCommunication(GPIO_TypeDef *cs_port, int cs_pin) {

	gpio_low(cs_port, cs_pin);
}
void spi_stopCommunication(GPIO_TypeDef *cs_port, int cs_pin) {
	gpio_high(cs_port, cs_pin);
}

bool spi_transmitReceive(SPI_TypeDef* spi, uint8_t* transmission, uint8_t *reception, uint16_t size, bool dma) {
	while (size-- >= 1) {
		// wait for TXFIFO to be empty
		while(!(spi->SR & SPI_SR_TXE));	// TXE = TX Empty
		if (transmission == NULL) {
			// send a dummy byte to trigger the clock pulses
			*((volatile uint8_t*) &(spi->DR)) = SPI_DUMMY_BYTE;
		} else {
			// fill TXFIFO with the instruction
			*((volatile uint8_t*) &(spi->DR)) = *transmission;
			transmission++;
		}
		while(!(spi->SR & SPI_SR_TXE));

		// read the reception line until it's empty
		while (spi->SR & SPI_SR_RXNE) {	// RXNE = RX Not Empty
			if (reception == NULL) {
				spi->DR;
			} else {
				*reception = spi->DR;
				reception++;
			}
		}
	}
	return true;
}
