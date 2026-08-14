#include <stdint.h>
#include "platform_init.h"
#include "Radio/AX5043.h"
#include <TestDefinition.h>

#define RUN_TEST	0	// 0 = run, 1 = run a very specific test
#define TEST_ID 	0	// ID of the test to run in case RUN_TEST = 1


bool test_radio_reads_simple();

int main(void)
{
    /* Loop forever */
	init_platform();

	#if (RUN_TEST==1) && (TEST_ID != 0)

    void (*testFunc)();
    testFunc = getTestFunction(TEST_ID);
    testFunc();

    #else

	//TODO: use RTC first_time flag.
	//if (first_time) {
	//  init_first_time()
	//}

	while (1) {
		continue;
	}

#endif

}