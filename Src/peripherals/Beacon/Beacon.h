#ifndef BEACON_H
#define BEACON_H

#include <stdint.h>

/**
 * Schedules periodic RTC callback for radio transmission with a message
 */
uint32_t beacon_init(char* arr, int size);

/**
 * Beacon callback for radio transmission
 */
void beacon_ping(char* arr, int size);

/**
 * Ends callbacks for radio transmissions
 */
void beacon_stop();

#endif