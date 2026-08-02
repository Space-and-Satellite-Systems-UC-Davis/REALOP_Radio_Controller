/*
 * log_record_tester.c
 *
 *  Created on: Aug 2, 2026
 */

// Copy of intercomm_test.c
// Do not want to rely on it staying the same. Also want the same test ID

#include "Flight_Computer/Intercomm.h"
#include "UART/crc.h"
#include "UART/uart.h"
#include "Timers/timers.h"

#define PFC_USART USART1

void testFunction_LogDownlink() {
    usart_init(PFC_USART, 9600);

    //Length of chunks being sent in bytes between PFC, Radio, and Ground
    //Time between upload requests in seconds

	uint8_t chunk[MAX_MESSAGE_BYTES];

    while(1) {
		int read_status = crc_read(USART1, chunk);
        // printMsg("Read %d\r\n", read_status);
    	if (read_status != -1) {
    		handleInput(USART1, chunk);
    	}
    }
}
