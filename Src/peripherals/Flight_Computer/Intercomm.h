//This file was written in cpp before ??

#include "Radio/radio.h"
#include "UART/pcp.h"

uint8_t* getEmptyChunk(size_t size);

void downloadData(PCPDevice *dev, uint8_t chunk[]);

void uploadData(PCPDevice *dev);

void sendState(PCPDevice *dev);

void transferToGround(PCPDevice *dev, uint8_t chunk[]);

//Primary function from which everything else here is called
void handleInput(PCPDevice *dev, uint8_t chunk[]);

