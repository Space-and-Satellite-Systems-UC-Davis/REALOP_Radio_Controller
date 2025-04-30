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

	const int CHUNK_LENGTH = 8;

	PCPDevice pcp;
	make_pcpdev(&pcp, USART1);

	uint8_t chunk[8] = {'1', '2', '3', '4'};

    while(1) {
    	nop(1);
    	int read_status = pcp_read(&pcp, chunk);
    	if (read_status != -1) {
    		handleInput(&pcp, chunk);
    	}
    }
}
