#include "Flight_Computer/Intercomm.h"
#include "UART/crc.h"
#include "UART/uart.h"
#include "Timers/timers.h"

void testFunction_Radio2PFCAPI() {
    usart_init(USART1, 9600);

    //Length of chunks being sent in bytes between PFC, Radio, and Ground
    //Time between upload requests in seconds

	uint8_t chunk[MAX_MESSAGE_BYTES];

	uint64_t start_time = getSysTime();
    while(1) {
    	usart_transmitBytes(USART1, "HELP???", 7);
    	// int read_status = crc_read(USART1, chunk);
    	// if (read_status != -1) {
    	// 	handleInput(USART1, chunk);
    	// }
    }
}