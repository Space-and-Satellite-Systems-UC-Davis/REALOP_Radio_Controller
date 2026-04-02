#include "Beacon.h"
#include <stdint.h>
#include <stdbool.h>

void testFunction_beacon() {

    static char arr[50] = "transmit test \n";

    uint32_t beacon_id = beacon_init(arr, 50);
    printMsg("beacon init w/ id: %u\n", beacon_id);
  
    for (int i = 0; i < 50000000; i++) {
        // printMsg("l\n");
    }
    printMsg("beacon stop\n");  
    printMsg("beacon id: %u\n", beacon_id);
    beacon_stop(beacon_id);

    printMsg("DONE WITH TEST\n");
}
