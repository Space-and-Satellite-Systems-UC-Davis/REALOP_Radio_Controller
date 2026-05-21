#include "uart.h"
#include "DMA/DMA.h"

#define RX_BUFFER_SIZE 128
uint8_t dma_rx_buffer[RX_BUFFER_SIZE];
uint16_t cpu_read_index = 0;

void testFunction_UART(){
    //testing PFC-->Radio UART connection
    //also testing Radio debug UART ig
    //send anything from PFC--> Radio
    //this test function should print out what was sent every 5 seconds
    //printMsg should be configured to the debug pin in USART3
    usart_init(USART1, 9600);
	usart_receiveBytesDMA(SELECT_USART1_RX, dma_rx_buffer, RX_BUFFER_SIZE);
	while(1) {
		// 1. Calculate where the DMA hardware is currently writing
		// CNDTR counts down from RX_BUFFER_SIZE to 0
		uint16_t dma_write_index = RX_BUFFER_SIZE - DMA1_Channel5->CNDTR; 
		// 2. Check if the DMA has moved ahead of our software read pointer
		printMsg("cpu_read_index: %d, dma_write_index: %d\r\n", cpu_read_index, dma_write_index);
		while (cpu_read_index != dma_write_index) {
			// Read the character
			char c = dma_rx_buffer[cpu_read_index];
			printMsg("received: %c\r\n", c);

			// Advance the software read pointer, wrapping around if necessary
			cpu_read_index = (cpu_read_index + 1) % RX_BUFFER_SIZE;
		}
	}
}