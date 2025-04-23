#include <stdint.h>
#include "UART/pcp.h"
#include "UART/uart.h"
//#include "Timers/timers.h"
#include "platform_init.h"

int main(void) {
    init_platform();
    usart_init(USART1, 9600);

	PCPDevice pcp;
	make_pcpdev(&pcp, USART1);

    while(1) {
    	handleInput(&pcp, 'S');
        pcp_retransmit(&pcp);
    	nop(10000);
    }
}
