#ifndef BEACON_H
#define BEACON_H

#include <stdint.h>

/**
 * Schedules periodic RTC callback for radio transmission
 */
uint32_t beacon_init();

/**
 * Beacon callback for radio transmission
 */
void beacon_ping();

/**
 * Ends callbacks for radio transmissions
 */
void beacon_stop();

#endif