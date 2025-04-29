#include <stdint.h>
//#include "print_scan.h"
#include "UART/pcp.h"
#include "UART/uart.h"
//#include "Timers/timers.h"
#include "platform_init.h"
#include "Flight_Computer/Intercomm.h"

int main(void) {
    init_platform();
    usart_init(USART1, 9600);

	PCPDevice pcp;
	make_pcpdev(&pcp, USART1);

	uint8_t chunk[8] = {'1', '2', '3', '4'};
    while(1) {
    	if (pcp_read(&pcp, chunk) != -1) {
    		handleInput(&pcp, chunk[0]);
    	}
    }
}
