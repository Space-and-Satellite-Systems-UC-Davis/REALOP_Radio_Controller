/*
 * uart.h
 *
 *  - August 18, 2023
 *  	Author	: Darsh
 *  	Log		: Copied from IntelliSat, modified for Radio Controller
 */

#include "uart.h"

/** IMPORTANT: Dealing with Revision Changes
 * Things to change across revisions:
 * 		- USART HELPERS
 * 			- Ensure the correct USART_ReceiverBuffer are declared
 * 			  based on the USART hardwares in use for that revision
 * 			- Ensure the uart_revisionBusDistinguisher() function is
* 			  inline with the USART hardwares in use for that revision
* 		- GPIO HELPERS
* 			- For each gpio_init(), ensure the right pins are
* 			  initialized, depending on the pinout for that revision
*		- USART INTERRUPTS
*			- Ensure the correct USART Hardwares have their interrupts
*			  defined
 */

/************************ USART HELPERS ************************/

#define ReceiveBufferLen 128
struct _rx_fifo {
	uint8_t buffer[ReceiveBufferLen];
	uint16_t front;
	uint16_t rear;
	bool timedout;
};
typedef struct _rx_fifo USART_ReceiverBuffer;

//USART_ReceiverBuffer USART1_RxBuffer;

USART_ReceiverBuffer* uart_revisionBusDistinguisher(USART_TypeDef *bus) {
	USART_ReceiverBuffer *rxbuff = NULL;

//	if (bus == USART1) {
//		rxbuff = &USART1_RxBuffer;
//	}

	return rxbuff;
}

#define enqueueBuffer(buff,usart) buff.buffer[buff.rear] = usart->RDR; \
							      buff.rear = (buff.rear + 1) % ReceiveBufferLen;

/************************ GPIO INITIALIZATION HELPERS ************************/

void usart1_gpio_init() {
	return;
}
void usart2_gpio_init() {
	return;
}

void usart3_gpio_init() {
	return;
}

void lpuart_gpio_init() {
	return;
}


/*************************** USART INITIALIZATIONS ***************************/

void uart_8bit_1stop(USART_TypeDef *bus, int baud_rate, bool rts_cts_control) {
	// all UARTs use HSI16 as per core_cofig.c,init_core_clocks()
	uint32_t uart_clock_speed = 16000000;
	if (bus == LPUART1) {
		// prep for baud rate calculation
		uart_clock_speed *= 256;
	}

	// disables UART and any random default configurations
	bus->CR1 = 0;

	// Configurations:
	//   - Word Size to 8 bits (M0:M1 = 00)
	//   - Baud rate to `baud_rate`
	//   - Stop Bit to 1 bit   (STOP = 00)
	bus->CR1 &= ~(USART_CR1_M0 | USART_CR1_M1);
	bus->BRR = uart_clock_speed / baud_rate;
	bus->CR2 &= ~USART_CR2_STOP;

	// Enable
	bus->CR1 |= USART_CR1_UE;	// UART
	bus->CR1 |= USART_CR1_RE;	// Hardware Receiver

	if (rts_cts_control) {
		bus->CR3 |= (USART_CR3_RTSE | USART_CR3_CTSE);
	}

	// Enable Interrupts
	bus->CR1 |= USART_CR1_RXNEIE;	// Receiver Interrupt
//	bus->CR1 |= USART_CR1_RTOIE;	// Timeout Interrupt
}


bool usart_init(USART_TypeDef *bus, int baud_rate) {
	switch((int)bus) {
		case (int)USART1:
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			usart1_gpio_init();
			uart_8bit_1stop(USART3, baud_rate, true);
			break;
		case (int)USART2:
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
			usart2_gpio_init();
			break;
		case (int)USART3:
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
			usart3_gpio_init();
			uart_8bit_1stop(USART3, baud_rate, false);
			break;
		case (int)LPUART1:
			RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
			lpuart_gpio_init();
			uart_8bit_1stop(LPUART1, baud_rate, false);
			break;
		default:
			return false;
	}
	return true;
}

/**************************** USART TRANSMITTER ****************************/

void usart_transmitChar(USART_TypeDef *bus, char c) {
	// Enable UART3 and Transmitter
	bus->CR1 |= USART_CR1_UE | USART_CR1_TE;

	// Place the character in the Data Register
	bus->TDR = c;

	// Wait for the Transfer to be completed by monitoring the TC flag
	while(!(bus->ISR & USART_ISR_TC));
}

void usart_transmitBytes(USART_TypeDef *bus, uint8_t message[]) {
	// Enable UART3 and Transmitter
	bus->CR1 |= USART_CR1_UE | USART_CR1_TE;

	// Transfer each character one at a time
	for (int i = 0; i < (int)strlen(message); i++){
		// wait until Data register is empty
		while (!(bus->ISR & USART_ISR_TXE));
		// Place the character in the Data Register
		bus->TDR = message[i];
	}

	// Wait for the Transfer to be completed by monitoring the TC flag
	while(!(bus->ISR & USART_ISR_TC));
}

/**************************** USART RECEIVER ****************************/

bool usart_recieverTimedOut(USART_ReceiverBuffer *rx) {
	if (rx->timedout) {
		rx->timedout = false;
		return true;
	} else {
		return false;
	}
}

bool usart_recieveBufferNotEmpty(USART_TypeDef *bus) {
	USART_ReceiverBuffer *rxbuff = uart_revisionBusDistinguisher(bus);
	if (rxbuff == NULL) {
		return false;
	}

	return (rxbuff->front != rxbuff->rear);
}

int usart_recieveBytes(USART_TypeDef *bus, uint8_t buffer[], uint16_t size) {
	USART_ReceiverBuffer *rxbuff = uart_revisionBusDistinguisher(bus);
	if (rxbuff == NULL) {
		return false;
	}

	uint16_t sz = 0;
	while (sz < size) {
		if (rxbuff->front != rxbuff->rear) {	// rxbuff not empty
			buffer[sz++] = rxbuff->buffer[rxbuff->front];
			rxbuff->front = (rxbuff->front + 1) % ReceiveBufferLen;
		}

		if (usart_recieverTimedOut(rxbuff)) {
			break;
		}
	}

	return sz;
}

/**************************** USART INTERRUPTS ****************************/

void USART1_IRQHandler() {
	if (USART1->ISR & USART_ISR_RXNE) {
		USART1->ISR &= ~USART_ISR_RXNE;
//		enqueueBuffer(USART1_RxBuffer, USART1);
	}
	if (USART1->ISR & USART_ISR_RTOF) {
		USART1->ISR &= ~USART_ISR_RTOF;
//		USART1_RxBuffer.timedout = true;
	}
}

void USART2_IRQHandler() {
	if (USART2->ISR & USART_ISR_RXNE) {
		USART2->ISR &= ~USART_ISR_RXNE;
	}
	if (USART2->ISR & USART_ISR_RTOF) {
		USART2->ISR &= ~USART_ISR_RTOF;
	}
}

void USART3_IRQHandler() {
	if (USART3->ISR & USART_ISR_RXNE) {
		USART3->ISR &= ~USART_ISR_RXNE;
	}
	if (USART3->ISR & USART_ISR_RTOF) {
		USART3->ISR &= ~USART_ISR_RTOF;
	}
}

void LPUART1_IRQHandler() {
	if (LPUART1->ISR & USART_ISR_RXNE) {
		LPUART1->ISR &= ~USART_ISR_RXNE;
	}
	if (LPUART1->ISR & USART_ISR_RTOF) {
		LPUART1->ISR &= ~USART_ISR_RTOF;
	}
}

