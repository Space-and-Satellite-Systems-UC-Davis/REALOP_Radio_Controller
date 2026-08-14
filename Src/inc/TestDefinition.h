#pragma once

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//                           TEST DECLARATIONS
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

extern void testFunction_Nothing();
extern void testFunction_radiooooo();
extern void testFunction_Radio2PFCAPI();
extern void testFunction_beacon();
extern void testFunction_RTC_Alarm();
extern void testFunction_UART();
extern void testFunction_AES128_Round_Trip();
extern void testFunction_FAE();

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//                           TEST REGISTRATION
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// Function that returns a pointer to a void function
void (*getTestFunction(int test_id))(void) {
	//! Every case must return a void function
	switch (test_id) {
		case 0:
			return testFunction_Nothing;
		case 1:
			return testFunction_radiooooo;
		case 2:
			return testFunction_beacon;
		case 3:
      return testFunction_AES128_Round_Trip;
		case 10:
			return testFunction_UART;
		case 18:
			return testFunction_RTC_Alarm;
		case 21:
			return testFunction_Radio2PFCAPI;
		case 31:
			return testFunction_FAE;
        default:
			return testFunction_Nothing;
	}
	return testFunction_Nothing;
}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//                           	  EXTRAS
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

void testFunction_Nothing() {
	while(1);
}
