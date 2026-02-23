#include "uart.h"

void testFunction_UART(){
    //testing PFC-->Radio UART connection
    //also testing Radio debug UART ig
    //send anything from PFC--> Radio
    //this test function should print out what was sent every 5 seconds
    //printMsg should be configured to the debug pin in USART3
    usart_init(USART1, 9600);
	while(1){
		delay_ms(5000);
		while(usart_receiveBufferNotEmpty(USART1)){
			char one[1];
			usart_receiveBytes(USART1, one, 1);
			printMsg("%c", one[0]);
		}
		printMsg(":)\r\n");
	}
}