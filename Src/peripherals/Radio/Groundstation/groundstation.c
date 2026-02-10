#include <UART/uart.h>
#include "../AX5043.h"
#define RadiotoPi             USART3
#define RadioUartBaudRate     9600
#define ReceiveBufferSize     256

static bool gs_enabled = false; 

// Radio to Pi
void EXTI2_IRQHandler(){
    if (!gs_enabled) {
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
    else {
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
	    	for(int i = 0; i<size; i++){
	    		arr[count + i] = packet.pkt[i];
	    	}
	    	if(size > 0)
	    		count += size;
	    } while(count < 1000 && !packet.isPacketEnd);
        uint8_t buffer[8];
	    
        for(int i = 0; i< 1000; i++){
	    	printMsg("%c", arr[i]);
            buffer[i%8] = arr[i]
            if (i % 8 == 7) usart_transmitBytes(RadiotoPi, buffer, 8);
	    }
	    NVIC_EnableIRQ(EXTI2_IRQn);
    }
}

// Pi to radio
void USART3_IRQHandler() {
	if (USART3->ISR & USART_ISR_RXNE) {
		USART3->ISR &= ~USART_ISR_RXNE;
	}
	if (USART3->ISR & USART_ISR_RTOF) {
		USART3->ISR &= ~USART_ISR_RTOF;
	}
	uint8_t buffer[ReceiveBufferSize] = {};
    uint16_t amount_read = usart_receiveBytes(RadiotoPi, buffer, ReceiveBufferSize);
    radio_transmit(amount_read, buffer, UHF_SPI);


}

void groundstation_init() {
	gs_enabled = true;
    usart_init(RadiotoPi, RadioUartBaudRate);
	radio_init();
}



void testFunction_groundstation() {
    #ifdef
	usart_init(RadiotoPi, RadioUartBaudRate);

    uint8_t *data = "Some characters";
    usart_transmitBytes(RadiotoPi, data);

    uint8_t buffer[ReceiveBufferSize] = {};
    uint16_t amount_read = usart_receiveBytes(RadiotoPi, buffer, ReceiveBufferSize);


}