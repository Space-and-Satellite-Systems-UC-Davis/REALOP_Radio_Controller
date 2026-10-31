/*
 * alarm_test.c
 *
 * Created on: Sep 3, 2025
 */
#include "RTC/rtc.h"
#include "print_scan.h"

void do_something1() { printMsg("Do something 1 \n\r"); }
void do_something2() { printMsg("Do something 2 \n\r"); }
void do_something3() { printMsg("Do something 3 \n\r"); }
void do_something4() { printMsg("Do something 4 \n\r"); }
void do_something5() { printMsg("Do something 5 \n\r"); }
void do_something6() { printMsg("Do something 6 \n\r"); }
void do_something7() { printMsg("Do something 7 \n\r"); } // should never be used

void testFunction_RTC_Alarm() {
	// For some reason when testing on A13,
	// rtc was only configurable if using LSI??
	// If using LSI, expect +/- 3% error

	printMsg("\n\rStarting RTC alarm test \n\r");

	// Basic one shot callbacks one after the other
	rtc_scheduleCallback(5, 0, 0, false, do_something1);
	rtc_scheduleCallback(15, 0, 0, false, do_something2);
	rtc_scheduleCallback(30, 0, 0, false, do_something3);
	uint32_t id = rtc_scheduleCallback(35, 0, 0, false, do_something6);

	// Schedule a callback to run in the middle of other tasks
	rtc_scheduleCallback(10, 0, 0, false, do_something4);

	// Schedule a recurring callback 
	rtc_scheduleCallback(20, 0, 0, true, do_something5);

	// Schedule a recurring callback to delete
	uint32_t id2 = rtc_scheduleCallback(20, 0, 0, true, do_something7);

	// Check if entry is there
	uint32_t res1 = rtc_isEntryActive(id);
	printMsg("Is entry active: %d\n\r", res1);
	uint32_t res2 = rtc_getEntry(id).unix_time;
	printMsg("When entry is going to be called: %d\n\r", res2);

	uint32_t res3 = rtc_deleteEntry(id);
	printMsg("Deleting of one shot entry response: %d\n\r", res3);

	// Check if entry is there after deleting it
	uint32_t res4 = rtc_isEntryActive(id);
	printMsg("Is deleted one shot entry active: %d\n\r", res4);
	// Expect 134232923
	uint32_t res5 = rtc_getEntry(id).unix_time;
	printMsg("When entry is going to be called: %d\n\r", res5);

	// // Make sure continuous entry stops
	uint32_t res6 = rtc_deleteEntry(id2);
	printMsg("Deleting of continous entry response: %d\n\r", res6);
	// Check if continuous entry is there
	uint32_t res7 = rtc_isEntryActive(id2);
	printMsg("Is deleted continous entry active: %d\n\r", res7);


	// Kill everything
	rtc_scheduleCallback(45, 0, 0, false, rtc_deleteAllEntries);

	// Expected output:
	/*
	 * 	Starting RTC alarm test
	 * 	Is entry active: 1
	 * 	When entry is going to be called: 40 //(or 41. Somewhere around that)
	 * 	Deleting of entry response: 1
	 * 	Is deleted one shot entry active: 0
	 * 	When entry is going to be called: 4294967295
	 *  Deleting of continous entry: 1
	 *	Is deleted continous entry active: 0
	 * 	Do something 1
	 * 	Do something 4
	 * 	Do something 2
	 * 	Do something 5
	 * 	Do something 3
	 * 	Do something 5
	 *
	 */

	while (true) {
		continue;
	}
}

