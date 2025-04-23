//#include "UART/pcp.h"
//
//void sendState(PCPDevice *dev);
//
//void prepareToRX(PCPDevice *dev);
//
//void listenToTX(PCPDevice *dev);
//
////OLD
////int* transferToRadioRequest();
////
////void received_Transfer_GroundStation_Request();
////
////void received_State_of_Radio_Request();
////
//
//
//
//
//

//This file was written in cpp before ??

#include "Radio/radio.h"
#include "UART/pcp.h"


//this is a function FOR NOW. See if needed to retransmit often.
int sendChunk(PCPDevice *dev, uint8_t chunk[]);

void downloadData(PCPDevice *dev);

void uploadData(PCPDevice *dev);

void transferToGround(PCPDevice *dev);

void sendState(PCPDevice *dev);

//Primary function from which everything else here is called
void handleInput(PCPDevice *dev, char input);

