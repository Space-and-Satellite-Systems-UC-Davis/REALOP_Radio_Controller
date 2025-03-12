#include <stdint.h>
//#include "print_scan.h"
#include "UART/pcp.h"
#include "UART/uart.h"
//#include "Timers/timers.h"
#include "platform_init.h"

int main(void)
{
    init_platform();
    usart_init(USART1, 9600);

    // PCPDevice* pcp = NULL;
    // make_pcpdev(pcp, USART1);

//    nop(1000);

    while(1) {
    	//pcp_transmit(pcp, "H", 1);
    	usart_transmitStr(USART1, "Z");
	nop(1000);

//		test[0] = 'B';
//    	usart_transmitBytes(USART1, test, 1);
//		nop(10000);
    }
}
