#include "Radio/AX5043.h"
#include "RTC/rtc.h"
#include <print_scan.h>

// static const char msg[] = "hi"; 

void beacon_ping() {

    // replace with transmit later
    printMsg("ping\n");

}

uint32_t beacon_init() {

    return rtc_scheduleCallback(1, 0, 0, true, beacon_ping);

}

void beacon_stop(uint32_t id) {

    bool temp = rtc_deleteEntry(id);
    if (temp) {
        printMsg("beacon found\n");
    } else {
        printMsg("beacon not found\n");
    }

    // rtc_deleteAllEntries();

} 

