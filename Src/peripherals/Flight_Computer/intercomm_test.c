#include "UART/crc.h"
#include "intercomm.h"

#define ICUSART USART1

int testFunction_Radio2PFC() {
    usart_init(ICUSART, 9600);
	
    //Time between upload requests in seconds
    const int WAIT_INTERVAL = 5;

	uint8_t chunk[CHUNK_LENGTH];

	uint64_t start_time = getSysTime();
    while(1) {
	    crc_transmit(ICUSART, "Hewwo?", 6);
    	int read_status = crc_read(ICUSART, chunk);
    	if (read_status != -1) {
    		handleInput(ICUSART, chunk);
    	}

    	// if (getSysTime() > (start_time + (1000*WAIT_INTERVAL))) {
    	// 	uploadData(USART1);
    	// 	start_time = getSysTime();
    	// }
    }
}