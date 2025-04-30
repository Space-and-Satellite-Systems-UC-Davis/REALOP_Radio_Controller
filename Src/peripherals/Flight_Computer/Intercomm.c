//This file was written in cpp before ??

#include "Intercomm.h"

typedef enum {
    DownloadData = 'D', //Receive data from PFC
    UploadData = 'U', //Transfer data to PFC
	SendState = 's', //Send state to PFC
	TransferToGround = 'T', //Transfer data to ground station
} MessageType;

typedef enum {
    TXactive = 't', //Busy tranceiving data to ground station
	RXactive = 'r', //Busy receiving data from ground station
    Idle = 'o', //Not busy
} State;

State current_state = Idle;

//Length of chunks being sent in bytes
//Later adjust to account for PCP overhead
const size_t CHUNK_LENGTH = 8;


//this is a function FOR NOW. See if needed to retransmit often.
int sendChunk(PCPDevice *dev, uint8_t chunk[]) {
    int response = pcp_transmit(dev, chunk, CHUNK_LENGTH);

    return response;
}
void downloadData(PCPDevice *dev) {

}

void uploadData(PCPDevice *dev) {

}

void transferToGround(PCPDevice *dev, uint8_t chunk[]) {
	current_state = TXactive;

	uint8_t n_chunks = chunk[1];

	//HERE BE DRAGONS
	//Whenever ground communication is written it will go here
		//Send n_chunks of radio memory to ground
		//May change based on ground comm interface
}

void sendState(PCPDevice *dev) {
	uint8_t state_chunk[CHUNK_LENGTH];
	state_chunk[0] = current_state;

	sendChunk(dev, state_chunk);
}

//Primary function from which everything else here is called
void handleInput(PCPDevice *dev, uint8_t chunk[]) {
	//Character command must be the first char
	switch (chunk[0]) {
		case DownloadData: downloadData(dev); break;
		case UploadData: uploadData(dev); break;
		case SendState: sendState(dev); break;
		case TransferToGround: transferToGround(dev, chunk); break;
	}
}
