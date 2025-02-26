#include <stdint.h>
#include "print_scan.h"
#include "UART/pcp.h"
#include "UART/uart.h"
#include "platform_init.h"




#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    init_platform();
    usart_init(USART1, 9600);

//    PCPDevice* pcp;
//    make_pcpdev(pcp, USART1);

    nop(2);

    uint8_t test[1];
    while(1) {
        test[0] = 'A';
    	usart_transmitBytes(USART1, test, 1);
//		nop(10000);

//		test[0] = 'B';
//    	usart_transmitBytes(USART1, test, 1);
//		nop(10000);
    }

//    while (1) {
//    	usart
//        uint8_t buffer[1];
//		int size = pcp_receive(pcp, buffer);
//		//If received a character. NOT HANDLING ERROR FROM pcp_receive (-1)
//		if (size > 0) {
//
//
//			//HERE BE DRAGONS
//			//handleIdle(buffer[0]);
//
//		}
//
//        // how is the state switch going to work how can i reenter the main functino
//        // whle another function is running and send a state
//
//        nop(1000); //Is nop necessary ?
//    }
}
