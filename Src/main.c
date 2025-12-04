#include <stdint.h>
//#include "print_scan.h"
#include "UART/crc.h"
#include "UART/uart.h"
#include "Timers/timers.h"
#include "platform_init.h"
#include "Flight_Computer/Intercomm.h"

int main(void) {
    init_platform();
    usart_init(USART1, 9600);
	
    //Time between upload requests in seconds
    const int WAIT_INTERVAL = 5;

	uint8_t chunk[CHUNK_LENGTH];

	uint64_t start_time = getSysTime();
    while(1) {
    	int read_status = crc_read(USART1, chunk);
    	if (read_status != -1) {
    		handleInput(USART1, chunk);
    	}

    	// if (getSysTime() > (start_time + (1000*WAIT_INTERVAL))) {
    	// 	uploadData(USART1);
    	// 	start_time = getSysTime();
    	// }
    }
}
