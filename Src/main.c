#include <stdint.h>
//#include "print_scan.h"
#include "UART/pcp.h"
#include "UART/uart.h"
#include "Timers/timers.h"
#include "platform_init.h"
#include "Flight_Computer/Intercomm.h"


int main(void) {
    init_platform();

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

    //Length of chunks being sent in bytes between PFC, Radio, and Ground
    const int CHUNK_LENGTH = 8;
    //Time between upload requests in seconds
    const int WAIT_INTERVAL = 5;

	PCPDevice pcp;
	make_pcpdev(&pcp, USART1);

	uint8_t chunk[CHUNK_LENGTH];

	uint64_t start_time = getSysTime();
    while(1) {
    	nop(1);
    	int read_status = pcp_read(&pcp, chunk);
    	if (read_status != -1) {
    		handleInput(&pcp, chunk);
    	}

    	if (getSysTime() > (start_time + (1000*WAIT_INTERVAL))) {
    		uploadData(&pcp);
    		start_time = getSysTime();
    	}
    }
}
