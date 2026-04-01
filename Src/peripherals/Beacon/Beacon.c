#include "Radio/AX5043.h"
#include "RTC/rtc.h"
#include <print_scan.h>

static char *beacon_arr;
static int beacon_size;

void beacon_ping_wrapper() {
    beacon_ping(beacon_arr, beacon_size);
}

void beacon_ping(char* arr, int size) {

    // transmit the message
    radio_transmit((size + 10), arr, UHF_SPI);
    // ping (attempt transmit)
    printMsg("pinging\n");

}

uint32_t beacon_init(char* arr, int size) {
    beacon_arr = arr;
    beacon_size = size;

    return rtc_scheduleCallback(1, 0, 0, true, beacon_ping_wrapper);
}

void beacon_stop(uint32_t id) {
    bool temp = rtc_deleteEntry(id);
    if (temp) {
        printMsg("beacon found\n");
    } else {
        printMsg("beacon not found\n");
    }
} 

