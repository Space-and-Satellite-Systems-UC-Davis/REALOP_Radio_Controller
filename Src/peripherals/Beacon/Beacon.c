#include "Radio/AX5043.h"
#include "RTC/rtc.h"
#include <print_scan.h>

// static const char msg[] = "hi"; 

void beacon_ping() {

    // replace with transmit later
    printMsg("bee\n");

}

void beacon_init() {

    rtc_scheduleCallback(0, 5, 0, true, beacon_ping);

}

