#ifndef BEACON_H
#define BEACON_H

/**
 * Schedules periodic RTC callback for radio transmission
 */
void beacon_init();

/**
 * Beacon callback for radio transmission
 */
void beacon_ping();

#endif