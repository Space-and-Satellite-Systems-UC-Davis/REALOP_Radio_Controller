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

// INSTRUCTIONS FOR TESTING (assuming CubeIDE debugger):
// 1. Flash the PFC with the test of the same name and ID
// 2. Use the debugger to check the first few fields of the log
//	  in radio_downlink_idle_log(). boot_counter and year/month
// 3. Set breakpoint on the end of crc_chunked_read() on Radio
// 4. Continue until it breaks there.
// 5. Open Intercomm.c and hover over "storedData"
// 6. That should show the contents. Check if bytes match what it was on PFC.
//    Should be some boot count number and then 0, 1, 1. Check step 2.
// 7. If you have the ability to read radio, check it's sending it correctly
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
