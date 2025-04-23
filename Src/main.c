#include <stdint.h>
//#include "print_scan.h"
#include "UART/pcp.h"
#include "UART/uart.h"
//#include "Timers/timers.h"
#include "platform_init.h"


//int main(void)
//{
//    init_platform();
//    usart_init(USART1, 9600);
//

//
//	pcp_transmit(&pcp , "Z", 2);
//
//	uint8_t buffer[2] = {111, 222};
//    while(1) {
////    	int result = pcp_read(&pcp, buffer);
//
////		usart_transmitStr(USART1, "Z");
//    	nop(1000);
//
//    	pcp_retransmit(&pcp);
//    }
//}


int main(void) {
    init_platform();
    usart_init(USART1, 9600);

	PCPDevice pcp;
	make_pcpdev(&pcp, USART1);

    while(1) {
    	handleInput(&pcp, 'S');
    	nop(10000);
    }
}

//
//int main(void) {
//    init_platform();
//
//    void (*testFunc)();
//    testFunc = getTestFunction(2);
//    testFunc();
//}
